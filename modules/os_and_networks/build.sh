#!/bin/bash
CURR_DIR="$( dirname -- "$0"; )"
gcc -o "$CURR_DIR"/main.o \
    "$CURR_DIR"/main.c \
    "$CURR_DIR"/src/processes.c
