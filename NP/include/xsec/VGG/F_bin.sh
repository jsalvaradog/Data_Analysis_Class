#!/bin/bash

# Define your function here

Run_Tot(){
(
echo 2 &&
echo 17 &&
echo 1 &&
echo 1 &&
echo 10.6 &&
echo 20 &&
echo 1 &&
echo 3 &&
echo $1 &&
echo $2 &&
echo $3 &&
echo $4 &&
echo $5 &&
echo $6 &&
echo $7) | ./dvcs
}

# Invoke your function
Run_Tot $1 $2 $3 $4 $5 $6 $7

