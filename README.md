<div align="center">
    <h1>RachitTracer</h1>
    <blockquote>
        A pathtracer fully written in pure C++ and SDL
    </blockquote>
</div>

# Status
MAJOR WORK IN PROGRESS

![Example Render](render.png)

# About
This project is meant to be a fully featured pathtracer based of the book *Raytracing in One Weekend*. It was originally started as an improvement to a python raytracing library I made a long time ago in middle school (called `resurgence_renderer`). The code for this older version can be found in the `Version 1` directory.

# Getting Started
Only requirement is g++ (or another C++ compiler) and SDL2 (with SDL_image). Because of my choice of language and libraries, it is decently portable.

*Steps tested on MacOS*
- Clone the repository to your desired directory.
- To compile, run: `make`
- To run the program, use the `RachitTracer` executable in `bin`, passing in an argument for the output file path:
    - Example: `./bin/RachitTracer render.png`
        - An image of the render will be written to the specified file and displayed on an SDL window (for easy viewing).
- To clean, run: `make clean`

# Credits
Much of the work here is based of Peter Shirley's amazing book: *Raytracing in One Weekend*