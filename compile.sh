#!/bin/bash
echo 'Compiling the files : '
ls Code/
g++ Code/*.cpp -o "$1" -lSDL2 -lSDL2_image