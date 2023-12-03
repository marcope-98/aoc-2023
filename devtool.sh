#!/bin/bash

function aoc() {
    if [ $# -ne 2 ]; then 
        echo "aoc [command] [day0X]"
        return
    fi

    command=$1
    day=$2
    case $command in
        create)
            echo "creating files in ./test/files/$day"
            mkdir ./test/files/$day
            touch ./test/files/$day/sample.txt
            touch ./test/files/$day/input.txt
            echo "creating test file ./test/src/$day-test.cpp"
            touch ./test/src/$day-test.cpp
            echo "creating header file ./include/aoc/solutions/$day.hpp"
            touch ./include/aoc/solutions/$day.hpp
            echo "creating source file ./src/solutions/$day.cpp"
            touch ./src/solutions/$day.cpp
            ;;
        delete)
            echo "removing directory ./test/files/$day"
            rm -rf ./test/files/$day
            echo "removing test file ./test/src/$day-test.cpp"
            rm ./test/src/$day-test.cpp
            echo "removing header file ./include/aoc/solutions/$day.hpp"
            rm ./include/aoc/solutions/$day.hpp
            echo "removing source file ./src/solutions/$day.cpp"
            rm ./src/solutions/$day.cpp
            ;;
        shortlist)
            echo create delete
            ;;
        *)
            echo "command not found"
            ;;
    esac


}


function _aoc() {
    local AVAILABLE_COMMANDS=$(aoc shortlist -)
    COMPREPLY=()
    if [ "$COMP_CWORD" -eq 1 ] ; then
        local cur=${COMP_WORDS[COMP_CWORD]}
        COMPREPLY=($( compgen -W "$AVAILABLE_COMMANDS" -- $cur ))
    fi
}

complete -o nospace -F _aoc aoc