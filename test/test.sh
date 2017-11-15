#!/bin/bash

printf "Starting Test...\n"

if [ -f ./examples/build/main.exe ]; then
    ./examples/build/main.exe log.dlog test || exit 1
elif [ -f ./examples/build/main.out ]; then
    ./examples/build/main.out log.dlog test || exit 1
fi

FILESIZE=$(stat -c%s "test.csv")

if [ ! "$FILESIZE" -eq 26529 ]; then
    printf "Incorrect file size\n"
    exit 1
fi

exit 0