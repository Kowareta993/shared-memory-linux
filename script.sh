#!/bin/bash
size=$1
find $"$2" -type d | sort | awk '$0 !~ last "/" {print last} {last=$0} END {print last}' | awk 'NR==1, NR=='$size