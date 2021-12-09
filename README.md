# Raykat
Simple raytracing engine in C (WIP).
Based on _Ray Tracing in One Weekend_ by Peter Shirley.

Watch [image.png](/image.png) for a rough estimate of what the raytracer is capable of at this moment.

![Progress image](/image.png)

## Build
This branch is in development and currently does NOT build. See [Todo](#Todo).

Build with make:
```console
$ make
```

To generate the image, run the make rule "image":
```console
$ make image
```

## Todo
I Completed the first book except for the materials. Here is what I'm planning to to next (eventually):
- [x] ~~Improve vector operations~~: Changed pointer params to const.
- [x] ~~Fix the coordinate system~~: This was really as easy as changing v-up.
- [ ] Materials: Partially implemented. (DOES NOT BUILD: Needs rewrite to proper functional style because hacked C OOP is not working as expected)
- [ ] Const correctness
- [ ] Command line arguments: Reading resolution and other settings from argv.
- [x] ~~Read geometry from file~~: Implemented a rudimentary obj parser. Loading objs with tons of tris slows down renders tremendously though.
- [ ] Environment maps.
- [ ] Threading: I have no experience with pthread.h so this ought to be fun.
- [ ] Textures.
- [ ] Volumes.

## References
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley
- [_raytracing-weekend_](https://github.com/Morozov-5F/raytracing-weekend) by Morozov-5F
- [_Fast, Minimum Storage Ray/Triangle Intersection_](https://www.graphics.cornell.edu/pubs/1997/MT97.pdf) by Thomas Möller and Ben Trumbore
