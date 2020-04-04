#!/bin/bash
if [ -z $1 ]; then
	echo "usage: " $0 "<directory>"
	exit
fi

num_dirs=0
num_files=0
for entry in $1/*
do
	#echo "$entry" #use a pair of double quotes in case the name of the item contains spaces
	if [ -d "$entry" ]; then #test whether the current "entry" is a subdirectory
		((num_dirs = num_dirs + 1))
	elif [ -f "$entry" ]; then #test whether the current "entry" is a file
		((num_files = num_files + 1))
	fi
done

echo "total number of subdirectories in $1 :" $num_dirs
echo "total number of files in $1:" $num_files
