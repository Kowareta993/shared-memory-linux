#!/bin/bash
size=$2
make clean
make write
make read
echo "--OUTPUT--"
./write $size $1 &
sleep 1
./read $size $1
echo "--END--"
make clean