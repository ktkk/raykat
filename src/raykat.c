#include "raykat.h"

#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>

#include "output.h"
#include "camera.h"
#include "scene.h"

#define IMG_HEIGHT 720
#define IMG_WIDTH 1080
#define ASPECT_RATIO ((double) IMG_WIDTH / (double) IMG_HEIGHT)
#define TOTAL_PIXELS (IMG_WIDTH * IMG_HEIGHT)
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH 50

/* ANSI colored output */
#define YELLOW "\e[0;33m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define RESETCOL "\e[0m"

color3 ray_color(ray* r, hittable_list* world, int depth) {
	hit_record rec;

	color3 black = {{ 0, 0, 0 }};
	if (depth <= 0) return black; // Recursion guard: return black if we've exceeded the bounce limit

	/* If object is hit */
	if (hittable_list_hit(world, r, 0.001, INFINITY, &rec)) {
		vec3 temp0 = vec3_add(&rec.p, &rec.normal);
		vec3 temp1 = vec3_random_unit_vector();
		//vec3 temp1 = vec3_random_in_hemisphere(&rec.normal);
		point3 target = vec3_add(&temp0, &temp1);

		ray temp2 = { rec.p, vec3_sub(&target, &rec.p) };
		color3 temp3 = ray_color(&temp2, world, depth - 1);
		return vec3_multiply_double(&temp3, 0.5);
	}

	/* Background lerp */
	vec3 unit_direction = vec3_norm(&r->direction);
	double hit = 0.5 * (unit_direction.y + 1.0);

	color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	color3 prod0 = vec3_multiply_double(&temp0, 1.0 - hit);
	color3 prod1 = vec3_multiply_double(&temp1, hit);
	/* blendedValue = (1 - hit) * startValue + hit * endValue */
	return vec3_add(&prod0, &prod1);
}

int main() {
	/* CANVAS */
	//pixel* pixel_arr = calloc(TOTAL_PIXELS, sizeof(pixel)); // Allocate on heap because default stack is too small

	/* WORLD */
	hittable_list* world = create_scene(SCENE_SPHERES);

	/* CAMERA */
	point3 lookfrom = {{ 3.5, 3, 1 }};
	point3 lookat = {{ 0, -1, 0 }};
	vec3 vup = {{ 0, 0, 1 }};
	double aperture = 0.1;
	vec3 temp0 = vec3_sub(&lookfrom, &lookat);
	double dist_to_focus = vec3_length(&temp0);
	//double dist_to_focus = 7.0;
	camera cam = camera_init(&lookfrom, &lookat, &vup, 20.0, ASPECT_RATIO, aperture, dist_to_focus);

	/* PREVIEW */
	hexcolor32* pixel_buffer;

	Display* display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "ERROR: could not open default display\n");
		exit(1);
	}

	bool mit_shm_available = XShmQueryExtension(display);
	if (!mit_shm_available)
		fprintf(stderr, "WARNING: could not find MIT-SHM extension\n");
	else
		fprintf(stderr, "INFO: detected MIT-SHM extension\n");

	int x = 1920 / 2 - (IMG_WIDTH / 2);
	int y = 1080 / 2 - (IMG_HEIGHT / 2);

	Window window = XCreateSimpleWindow(
			display, // Display
			XDefaultRootWindow(display), // Parent window
			x, y, // Coordinates
			IMG_WIDTH, IMG_HEIGHT, // Size
			0, // Border width
			0, // Border color
			0); // Background color (around the image, not the image background itself)

	XStoreName(display, window, "raykat preview"); // Window title

	XWindowAttributes win_attributes;
	XGetWindowAttributes(display, window, &win_attributes);

	XImage* image;

	XShmSegmentInfo shm_info;

	if (mit_shm_available) {
		/* Create shared memory segment */
		shm_info.readOnly = true;
		shm_info.shmid = shmget(IPC_PRIVATE, IMG_WIDTH * IMG_HEIGHT * sizeof(hexcolor32), IPC_CREAT | 0777);

		if (shm_info.shmid < 0) {
			fprintf(stderr, "ERROR: could not create a new shared memory segment: %s\n", strerror(errno));
			exit(1);
		}

		/* Map shared memory segment */
		pixel_buffer = shmat(shm_info.shmid, 0, 0);

		shm_info.shmaddr = (char*) pixel_buffer;

		if (shm_info.shmaddr == (void*) -1) {
			fprintf(stderr, "ERROR: could not memory map the shared memory segment: %s\n", strerror(errno));
			exit(1);
		}

		/* Attach shared memory segment to server */
		if (!XShmAttach(display, &shm_info)) {
			fprintf(stderr, "ERROR: could not attach the shared memory segment to the server\n");
			exit(1);
		}

		image = XShmCreateImage(display,
								win_attributes.visual,
								win_attributes.depth,
								ZPixmap,
								(char*) pixel_buffer,
								&shm_info,
								IMG_WIDTH,
								IMG_HEIGHT);
	}
	else {
		pixel_buffer = mmap(NULL,
					  IMG_WIDTH * IMG_HEIGHT * sizeof(hexcolor32),
					  PROT_READ | PROT_WRITE,
					  MAP_PRIVATE | MAP_ANONYMOUS,
					  -1,
					  0);

		if (pixel_buffer == MAP_FAILED) {
			fprintf(stderr, "ERROR: could not allocate memory for pixels: %s\n", strerror(errno));
			exit(1);
		}

		image = XCreateImage(display,
							 win_attributes.visual,
							 win_attributes.depth,
							 ZPixmap,
							 0,
							 (char*) pixel_buffer,
							 IMG_WIDTH, IMG_HEIGHT,
							 32,
							 IMG_WIDTH * sizeof(hexcolor32));
	}

	GC graphics_context = XCreateGC(display, window, 0, NULL);

	Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(display, window, &wm_delete_window, 1);

	XSelectInput(display, window, KeyPressMask | PointerMotionMask);

	XMapWindow(display, window);

	int completion_type = XShmGetEventBase(display) + ShmCompletion;

	bool safe_to_render = true;
	bool quit = false;

	/* RENDER */
	clock_t start = clock();

	printf("P3\n%d %d\n255\n", IMG_WIDTH, (int)IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */

	for (unsigned int i = 0; i < TOTAL_PIXELS; ++i) {
		color3 bg_color = {{ HEX_TO_RGB(PREVIEW_BG) }};
		pixel_buffer[i] = PREVIEW_BG;
		//pixel_arr[i].color_rgb = bg_color;
		//pixel_arr[i].color_hex = PREVIEW_BG;

		//pixel_arr[i].rendered = false;
	}

	unsigned int current_pixel = 0;

	while (!quit) {
		while (XPending(display) > 0) {
			XEvent event;
			XNextEvent(display, &event);

			switch (event.type) {
				case KeyPress: {
						switch (XLookupKeysym(&event.xkey, 0)) {
							case 'q':
								quit = true;
								break;
						}
					}
					break;
				case ClientMessage: {
						if ((Atom)event.xclient.data.l[0] == wm_delete_window) {
							quit = 1;
						}
					}
					break;
				default: {
						if (event.type == completion_type)
							safe_to_render = true;
					}
					break;
			}
		}

		if (safe_to_render) {
			if (mit_shm_available) {
				XShmPutImage(display, window, graphics_context, image, 0, 0, 0, 0, IMG_WIDTH, IMG_HEIGHT, true);
				safe_to_render = false;
			}
			else {
				XPutImage(display, window, graphics_context, image, 0, 0, 0, 0, IMG_WIDTH, IMG_HEIGHT);
			}

			int x = current_pixel % IMG_WIDTH;
			int y = current_pixel / IMG_HEIGHT;

			color3 pixel_color = {{ 0, 0, 0 }};

			//for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
			//	double u = (x + RAND_DOUBLE) / (IMG_WIDTH - 1);
			//	double v = (y + RAND_DOUBLE) / (IMG_HEIGHT - 1);

			//	ray r = camera_get_ray(&cam, u, v);
			//	color3 raycolor = ray_color(&r, world, MAX_DEPTH);
			//	pixel_color = vec3_add(&pixel_color, &raycolor);
			//}

			pixel_buffer[current_pixel] = RGB_TO_HEX(pixel_color.r, pixel_color.g, pixel_color.b);

			current_pixel++;
		}

		//for (unsigned int i = 0; i < TOTAL_PIXELS; ++i) {
		//	for (int y = IMG_HEIGHT - 1; y >= 0; --y) {
		//		fprintf(stderr, YELLOW "\rScanlines remaining: " RED "%3d" RESETCOL, y);
		//		fflush(stderr);

		//		for (int x = 0; x < IMG_WIDTH; ++x) {
		//			color3 bg_color = {{ HEX_TO_RGB(PREVIEW_BG) }};

		//			int idx = y * IMG_WIDTH + x;

		//			if (!pixel_arr[idx].rendered) {
		//				color3 pixel_color = {{ 0, 0, 0 }};

		//				for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
		//					double u = (x + RAND_DOUBLE) / (IMG_WIDTH - 1);
		//					double v = (y + RAND_DOUBLE) / (IMG_HEIGHT - 1);

		//					ray r = camera_get_ray(&cam, u, v);
		//					color3 raycolor = ray_color(&r, world, MAX_DEPTH);
		//					pixel_color = vec3_add(&pixel_color, &raycolor);
		//				}

		//				pixel_arr[idx].color_rgb = pixel_color;
		//				pixel_arr[idx].color_hex = RGB_TO_HEX(pixel_color.r, pixel_color.g, pixel_color.b);

		//				pixel_arr[idx].rendered = true;
		//			}
		//			else {
		//				pixel_arr[idx].color_rgb = bg_color;
		//				pixel_arr[idx].color_hex = RGB_TO_HEX(bg_color.r, bg_color.g, bg_color.b);
		//			}
		//		}
		//	}

		//	write_color_to_file(stdout, &pixel_arr[i].color_rgb, SAMPLES_PER_PIXEL);
		//}
	}

	// TODO(ktkk): Surround this loop with the window loop. Or find a different solution.
	//for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
	//	fprintf(stderr, YELLOW "\rScanlines remaining: " RED "%3d" RESETCOL, i);
	//	fflush(stderr);

	//	for (int j = 0; j < IMG_WIDTH; ++j) {
	//		color3 pixel_color = {{ 0, 0, 0 }};

	//		for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
	//			double u = (j + RAND_DOUBLE) / (IMG_WIDTH - 1);
	//			double v = (i + RAND_DOUBLE) / (IMG_HEIGHT - 1);

	//			ray r = camera_get_ray(&cam, u, v);
	//			color3 raycolor = ray_color(&r, world, MAX_DEPTH);
	//			pixel_color = vec3_add(&pixel_color, &raycolor);
	//		}

	//		write_color_to_file(stdout, &pixel_color, SAMPLES_PER_PIXEL);
	//	}
	//}

	clock_t diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;

	fprintf(stderr, GREEN "\nDone.\n" RESETCOL "Took %d seconds and %d milliseconds.\n", msec / 1000, msec % 1000);

	cleanup_scene(world);
}
