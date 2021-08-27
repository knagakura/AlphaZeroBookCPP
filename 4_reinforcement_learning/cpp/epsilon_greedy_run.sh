#!/bin/zsh

rm -r main.out
g++-11 -D DEBUG EpsilonGreedy.cpp -o main.out
./main.out
rm -r main.out