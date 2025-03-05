#!/bin/bash

## Individual code compilers.
## You must uncomment the main in the .c file and comment the section
## at the bottom before running these scripts.

#~ gcc -g -o circuit circuit.c -lcheck -lm -lrt -lsubunit -lcheck_pic
#~ ./circuit

####################

## Make unit tests and main

make -f make-test.mk 
./circuittest
./intensitytest
./main
