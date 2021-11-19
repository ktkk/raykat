#include <math.h>
#include "output.h"

#ifdef PREVIEW
bool init_preview_window(int width, int height) {
	// TODO(ktkk): Possibly make these vars global. Alternatively, move all this code to raykat main.

	/* Set up display */
	Display* display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "ERROR: could not open default display\n");
		return false;
	}

	/* Check MIT_SHM extention availability */
	bool mitShmAvailable = XShmQueryExtension(display);
	if (!mitShmAvailable)
		fprintf(stderr, "WARNING: could not find MIT-SHM extension\n");
	else
		fprintf(stderr, "INFO: detected MIT-SHM extension\n");

	/* Set up window */
	int x = 1920 / 2 - (WIDTH / 2);
	int y = 1080 / 2 - (HEIGHT / 2);

	Window window = XCreateSimpleWindow(
			display, // Display
			XDefaultRootWindow(display), // Parent window
			x, y, // Coordinates
			width, height, // Size
			0, // Border width
			0, // Border color
			0); // Background color (around the image, not the image background itself)

	XStoreName(display, window, "raykat preview"); // Window title

	XWindowAttributes winAttr;
	XGetWindowAttributes(display, window, &winAttr);

	/* Set up image */
	XImage* image;

	XShmSegmentInfo shmInfo;

	if (mitShmAvailable) {
		/* Create shared memory segment */
		shmInfo.readOnly = true;
		shmInfo.shmid = shmget(IPC_PRIVATE, width * height * sizeof(pixel32), IPC_CREAT | 0777);

		if (shmInfo.shmid < 0) {
			fprintf(stderr, "ERROR: could not create a new shared memory segment: %s\n", strerror(errno));
			return false;
		}

		/* Map shared memory segment */
		pixels = shmat(shmInfo.shmid, 0, 0);

		shmInfo.shmaddr = (char*) pixels;

		if (shmInfo.shmaddr == (void*) -1) {
			fprintf(stderr, "ERROR: could not memory map the shared memory segment: %s\n", strerror(errno));
			return false;
		}

		/* Attach shared memory segment to server */
		if (!XShmAttach(display, &shmInfo)) {
			fprintf(stderr, "ERROR: could not attach the shared memory segment to the server\n");
			return false;
		}

		image = XShmCreateImage(display,
								winAttr.visual,
								winAttr.depth,
								ZPixmap,
								(char*) pixels,
								&shmInfo,
								WIDTH,
								HEIGHT);
	}
}

void write_color_to_preview_window(color3* color, int samples_per_pixel) {
	//fprintf(stream, "%x\n",
	//		RGB_TO_HEX(clamp(r, 0.0, 0.999),
	//				   clamp(g, 0.0, 0.999),
	//				   clamp(b, 0.0, 0.999)));
}
#endif

void write_color_to_file(FILE* stream, color3* color, int samples_per_pixel) {
	double scale = 1.0 / samples_per_pixel;
	double r = sqrt(scale * color->r);
	double g = sqrt(scale * color->g);
	double b = sqrt(scale * color->b);

	/* Write out the translated [0, 255] value of each color component */
	fprintf(stream, "%d %d %d\n",
			CONVERT_COMPONENT(clamp(r, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(g, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(b, 0.0, 0.999))
		);
}
