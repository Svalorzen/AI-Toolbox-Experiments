How To
======

Requirements
------------

The project requires:

- CMake
- Compiler support for C++17 (so at least `g++-7`)
- Boost library
- The Eigen matrix library 3.3.

Instructions
------------

Look how to add the `AI-Toolbox` library dependency via git by reading (or
running) the `READ_ME_FIRST.sh` file. This will also remove the original remote
of the repo so you don't push to it!!

Then compile the project (please name the build folder `build` as the experiment
running/plotting code expects it like that).

```
mkdir build
cd build
cmake ..
make
```
