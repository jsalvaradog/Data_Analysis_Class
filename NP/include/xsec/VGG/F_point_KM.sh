#!/bin/bash

# Define your function here

Run_Tot(){
(
echo 3 &&
echo 4 &&
echo 3 &&
echo 1 &&
echo 63 &&
echo 2 &&
echo 3 &&
echo 1 &&
echo 1 &&
echo 1 &&
echo 3 &&
echo 1 &&
echo 10.6 &&
echo 3 &&
echo $1 &&
echo $2 &&
echo 0 &&
echo $3 &&
echo $4 &&
echo $4 &&
echo $4) | ./dvcs
}

# Invoke your function
Run_Tot $1 $2 $3 $4

