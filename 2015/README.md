# aoc

Advent Of Code solutions for 2015 using C99. Builds and runs on macOS, Linux, and OpenBSD.

## Building

Be sure to clone the top project with its submodules:

    git clone --recurse-submodules https://github.com/fputs/advent-of-code

This project relies on several BSD extensions to the stdlib. OpenBSD and macOS users should be able to build the project out of the box. Linux users will need `libbsd` installed. The package is called `libbsd-dev` on Debian-based systems.

Build the project using Cmake:

    mkdir build
    cd build
    cmake ..
    make

The supplied `build.sh` script does the above for you.

## Inputs

Inputs can be generated from `get_input.sh`. You will need to get your session cookie from the Advent of Code website. The easiest way to do this is to inspect any input page in your browser.

The script can then be run with `bash get_input.sh SESSIONCOOKIE`, with `SESSIONCOOKIE` replaced by your unique session cookie's hash.

## Usage

```bash
./advent $DAY
```

For example, `./advent 1` will run Day 01
