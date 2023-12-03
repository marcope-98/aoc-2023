# Advent of Code 2023

This repository is a collection of my solutions for the problems of Advent of Code 2023, written in the C++ programming language.

The project depends on GoogleTest which, if it's not already present in the system, will be downloaded and compiled locally.

## Tools

Some additional tools have been developed to simplify the creation of the necessary files for each day, i.e. VSCode snippets and a command line tool

### devtool

In order to create the necessary files for each day a command line tool has been developed in bash.

To access the commands available open a terminal and type:
```console
$ cd ./aoc-2023
$ source ./devtool.sh
```

The commands available are for now simply two and both accepts exactly two input arguments: the type of command and the name of the day to create/remove.

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

If you fail to provide exactly two input arguments the command line tool will exactly reminding you of how to properly use its functionalities.

In addition this command line tool provides auto-completion.


### VSCode Snippets

Once the necessary files have been generated manually or using the command line tool. It is possible to fill them with VSCode snippets located in `.vscode/aoc.code-snippets`.

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

Though suggestions and improvement are always welcome please bare in mind that:

![](https://github.com/marcope-98/aoc-2023/blob/master/media/IMG_0015.JPG)