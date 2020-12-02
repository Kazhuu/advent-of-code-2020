# advent-of-code-2020

My C++ solutions for a year 2020. All solutions and guides are done on Linux.

## Build and Run

To build use CMake with separate build directory and build with debug
information to support debugging with gdb.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

Then to run the executables you need to go to the build folder and pipe the
puzzle input for it

```
cd build/dayXX
cat input | ./dayXX
```
