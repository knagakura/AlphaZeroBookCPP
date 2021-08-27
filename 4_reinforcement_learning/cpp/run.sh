#!/bin/bash

rm -r main.out
g++-11 -O2 -std=gnu++17 -Wall -Wextra -DDEBUG ./main.cpp -o main.out
./main.out