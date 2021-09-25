# Raykat
Simple raytracing engine in C (WIP).
Based on _Ray Tracing in One Weekend_ by Peter Shirley.

Watch [image.png](/image.png) for a rough estimate of where I am through the course.

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
- [ ] Improve vector operations: Not sure if pass by pointer makes sense so I might remove that, which would lead to some major refactoring in the rest of the codebase.
- [ ] Fix the coordinate system: The book uses y-up, which is not what I'm used to so I intend on changing it to z-up.
- [ ] Materials: I intentionally skipped this because translating the course's polymorphism was a pain for the hittables.
- [ ] Command line arguments: Reading resolution and other settings from argv.
- [ ] Read geometry from file.
- [ ] Environment maps.
- [ ] Threading: I have no experience with pthread.h so this aught to be fun.
- [ ] Textures.
- [ ] Volumes.

## References
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley
- [_raytracing-weekend_](https://github.com/Morozov-5F/raytracing-weekend) by Morozov-5F
