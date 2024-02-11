# Advent of Code 2023

This repository is a collection of my solutions for the problems of Advent of Code 2023, written in the C++ programming language.

The project depends on GoogleTest which, if it's not already present in the system, will be downloaded and compiled locally.

Moreover, the projects relies on the Eigen3 library that must be downloaded and installed in your system.

## Tools

Some additional tools have been developed to simplify the creation of the necessary files for each day, i.e. VSCode snippets and a command line tool

### devtool

In order to create the necessary files for each day a command line tool has been developed in bash.

To access the commands available open a terminal and type:
```console
$ cd ./aoc-2023
$ source ./devtool.sh
```

The commands available are (for now) simply two and both accepts exactly two input arguments: the type of command and the name of the day to create/remove.

```console
$ aoc create dayXX
creating files in ./test/files/dayXX
creating test file ./test/src/dayXX-test.cpp
creating header file ./include/aoc/solutions/dayXX.hpp
creating source file ./src/solutions/dayXX.cpp
$
$ aoc delete dayXX
removing directory ./test/files/dayXX
removing test file ./test/src/dayXX-test.cpp
removing header file ./include/aoc/solutions/dayXX.hpp
removing source file ./src/solutions/dayXX.cpp
```

If you fail to provide exactly two input arguments the command line tool will remind you of how to properly use its functionalities.

In addition this command line tool provides auto-completion.


### VSCode Snippets

Once the necessary files have been generated (manually or using the command line tool). It is possible to fill them with VSCode snippets located in `.vscode/aoc.code-snippets`.

Their use is as follows:

- open `include/aoc/solutions/dayXX.hpp` and type `aoc-hpp`
- open `src/solutions/dayXX.cpp` and type `aoc-cpp`
- open `test/src/dayXX-test.cpp` and type `aoc-test`

In any of the above cases the file will be filled with the specified template and every instance of `DAYXX` or `dayXX` will be highlighted. Hence, you just need to type the corresponding day number `XX`.

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

By default the executable `./test/aoc_test` runs all tests. To run a test for a specific day or subsets use the command line argument `--gtest_list_tests` to list all available tests and `--gtest_filter=dayXX*` to run a specific day (replace `XX` with the number of the day).

E.g.
```console
$ ./test/aoc_test --gtest_list_tests           # List all tests
$ ./test/aoc_test --gtest_filter=day20*        # Run part1 and part2 of day20
```

Though suggestions and improvement are always welcome please bare in mind that:

![](https://github.com/marcope-98/aoc-2023/blob/master/media/IMG_0015.JPG)

## Results

Please understand that this project is not about speed or code performance but rather a fun way to pass the time. Therefore, I am completely aware that some of the techniques may not be as efficient or that better algorithms can be employed to speed up the implemented solutions.

My most recent running times are as follows. These results may vary.

```console
[----------] 2 tests from day01 (3 ms total)
[----------] 2 tests from day02 (1 ms total)
[----------] 2 tests from day03 (11 ms total)
[----------] 2 tests from day04 (4 ms total)
[----------] 2 tests from day05 (2 ms total)
[----------] 2 tests from day06 (0 ms total)
[----------] 2 tests from day07 (5 ms total)
[----------] 2 tests from day08 (9 ms total)
[----------] 2 tests from day09 (1 ms total)
[----------] 2 tests from day10 (4 ms total)
[----------] 2 tests from day11 (1 ms total)
[----------] 2 tests from day12 (66 ms total)
[----------] 2 tests from day13 (1 ms total)
[----------] 2 tests from day14 (77 ms total)
[----------] 2 tests from day15 (2 ms total)
[----------] 2 tests from day16 (932 ms total)
[----------] 2 tests from day17 (1324 ms total)
[----------] 2 tests from day18 (1 ms total)
[----------] 2 tests from day19 (3 ms total)
[----------] 2 tests from day20 (176 ms total)
[----------] 2 tests from day21 (2774 ms total)
[----------] 2 tests from day22 (35 ms total)
[----------] 2 tests from day23 (43794 ms total)
[----------] 2 tests from day24 (2 ms total)
[----------] 1 test  from day25 (176109 ms total)
[==========] 49 tests from 25 test suites ran. (225349 ms total)
[  PASSED  ] 49 tests.
```

> "Not my best year, but I have learned a lot"