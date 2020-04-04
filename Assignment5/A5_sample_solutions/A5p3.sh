#!/bin/bash

function printEquation { # a function that can accept two parameters
	((v = $1*$2))
	echo "$1 * $2 = $v"
}

for i in {1..3}
	do
	for j in {1..5}
		do
			printEquation $i $j #call our function with two parameters i and j
		done
	done
