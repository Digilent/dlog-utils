#!/bin/bash

printf "Starting Test...\n"

if [ -f ./examples/build/main.exe ]; then
    ./examples/build/main.exe log.dlog test || exit 1
elif [ -f ./examples/build/main.out ]; then
    ./examples/build/main.out log.dlog test || exit 1
else
    exit 1
fi

FILESIZE=$(stat -c%s "test.csv")

LINES=$(wc -l < test.csv)

if [ ! "$LINES" -eq 1780 ]; then
    printf "Invalid csv\n"
    exit 1
fi

printf "Test Completed Successfully\n"

exit 0