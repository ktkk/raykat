# Raykat
Simple raytracing engine in C (WIP).
Based on _Ray Tracing in One Weekend_ by Peter Shirley.

Watch [image.png](/image.png) for a rough estimate of what the raytracer is capable of at this moment.

![Progress image](/image.png)

## Build
Build with make:
```sh
make
```

To generate the image, run the make rule "image":
```sh
make image
```

## Todo
I Completed the first book except for the materials. Here is what I'm planning to to next (eventually):
- [x] ~~Improve vector operations~~: Changed pointer params to const.
- [x] ~~Fix the coordinate system~~: This was really as easy as changing v-up.
- [ ] Materials: I intentionally skipped this because translating the course's polymorphism was a pain for the hittables.
- [ ] Command line arguments: Reading resolution and other settings from argv.
- [ ] Read geometry from file.
- [ ] Environment maps.
- [ ] Threading: I have no experience with pthread.h so this ought to be fun.
- [ ] Textures.
- [ ] Volumes.

## References
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley
- [_raytracing-weekend_](https://github.com/Morozov-5F/raytracing-weekend) by Morozov-5F
- [_Fast, Minimum Storage Ray/Triangle Intersection_](https://www.graphics.cornell.edu/pubs/1997/MT97.pdf) by Thomas Möller and Ben Trumbore
