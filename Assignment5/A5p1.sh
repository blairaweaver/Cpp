#!/bin/bash

#check to make sure arguments are integers
re='^[0-9]+$'
for arg in "$@"
do
	if ! [[ $arg =~ $re ]]; then
		echo "$arg is not a number" >&2; exit 1
	fi
done

for arg in "$@"
do
	echo "$arg"
done

myArray=( "$@" )
numArg=$#
for ((i = 0; i < $numArg; i++))
do
	for ((j = 0; j < $numArg - i - 1; j++))
	do
		if ((${myArray[$j]} > ${myArray[$((j+1))]} ))
		then
			temp=${myArray[$j]}
			myArray[$j]=${myArray[$((j+1))]}
			myArray[$((j+1))]=$temp
		fi
	done
done

echo "After sorthing in numberical order"
for i in ${myArray[@]}
do
	echo "$i"
done
