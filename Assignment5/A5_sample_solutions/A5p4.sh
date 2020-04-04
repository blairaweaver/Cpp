#!/bin/bash
#you can call this script with "bash A5p4.sh <n>"

if [ -z $1 ]; then
	echo "usage: " $0 "<positive_integer>"
	exit
fi

for ((i=1;i<=$1;i++))
	do
		echo $i
	done
