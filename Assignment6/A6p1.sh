#!/bin/bash

if [ -z $1 ]; then
	echo "usage: " $0 "<directory>"
	exit
fi

num_dir=0
num_fil=0

for entry in $1/*
do
	if [ -d "$entry" ]; then
		((num_dir = num_dir + 1))
	else
		((num_fil = num_fil + 1))
	fi
done

echo "Number of files in " $1 ": " $num_fil
echo "Number of subdirectories in " $1 ": " $num_dir
