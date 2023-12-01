# Advent of Code 2023

This repository is a collection of my solutions for the problems of Advent of Code 2023, written in the C++ programming language.

The project depends on GoogleTest which, if it's not already present in the system, will be downloaded and compiled locally.

## Where's main?

There is no main. All the different implementations are developed as a static library and their correctness is tested using GoogleTest.

Hence, to build and execute the tests open a terminal and run the following commands:

```console
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ ./test/aoc_test
```

Though suggestions and improvement are always welcome please bare in mind that:

![](https://github.com/marcope-98/aoc-2023/blob/master/media/IMG_0015.JPG)