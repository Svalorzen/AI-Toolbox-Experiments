AI-Toolbox Experiments Setup Repository
=======================================

This repository exists as a quick starting point to setup your own repository
that uses the AI-Toolbox library. This is what I use myself so hopefully it
should help you as well.

It is for Linux only!

This repository is meant to be copied rather than cloned (or at least, once you
clone it, you should change the `git remote` to what you plan to use for your
own work). For this reason, I generally update this repository using
`force-push` rather than normal commits. Just a warning.

How To Use
==========

This repository uses CMake as the build framework; this allows it to seamlessly
integrate with the CMake setup of AI-Toolbox.

Requirements
------------

Using this setup repository has the same requirements of
[AI-Toolbox](https://github.com/Svalorzen/AI-Toolbox) (obviously, since that's
what it is meant to use). You can look them up on the project's main page.

Setup Instructions
------------------

The `DO_ME_FIRST.sh` script does all the setup work for you; you can either
read it and do what it says, or just execute it (run `chmod +x
./DO_ME_FIRST.sh`). It basically:

- Detaches your clone of this repository from this remote.
- Initializes the `git submodules` so that AI-Toolbox can be added.
- Adds AI-Toolbox as a submodule into the `deps/` folder (this automatically
  clones it as well).

Creating an Executable
----------------------

This project contains the setup I generally use to produce my own research, so
it is quite opinionated as it is basically my workflow. You are welcome to
change it if it doesn't suit you.

The main entry point is the `src/CMakeLists.txt` file. It contains predefined
functions (`AddExperimentMDP`, `AddExperimentPOMDP` and `AddExperimentFMDP`)
which are used to create new executables.

*These assume that the files to compile are in the form of `{name}_main.cpp`*.
If you do not want to follow this, either modify the CMakeList file to suit you,
or rewrite it from scratch however you prefer.

An example experiment file already exists in the `src/` folder, and it is
already setup to compile if you want to check that everything is working
correctly.

Compile the project (please keep the name the build folder `build` as the
experiment running/plotting code expects it like that).

```
mkdir build
cd build
cmake ..
make
```

Running and Plotting System
---------------------------

The resulting executables are placed in the `build/src` folder, and you can call
them manually from there or do whatever you want with them.

However, this repository also contains, in the `plot/` folder, some utilities
for parallel experiment running with multiple flags.

FEEL FREE TO DISREGARD THE ENTIRE THING IF IT IS TOO MESSY OR YOU DO NOT NEED
IT. It is just what I usually use.

If you are interested in using this system, please read the `README.md` file in
the `plot/` folder.
