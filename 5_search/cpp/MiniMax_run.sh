#!/bin/zsh

rm -r main.out
g++-11 -D DEBUG MiniMax.cpp -o main.out
./main.out
rm -r main.out