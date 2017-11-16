#!/bin/bash

printf "Starting Test...\n"

if [ -f ./examples/build/main.exe ]; then
    ./examples/build/main.exe log.dlog test || exit 1
elif [ -f ./examples/build/main.out ]; then
    ./examples/build/main.out log.dlog test || exit 1
else
    exit 1
fi

cmp ./test.csv ./test/success.csv || exit 2

printf "Test Completed Successfully\n"

exit 0