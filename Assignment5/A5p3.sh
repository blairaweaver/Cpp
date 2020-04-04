#!/bin/bash

math_equations () {
	echo "$1 * $2 = $(($1*$2))"
}

for i in {1..3}
do
	for j in {1..5}
	do
		math_equations $i $j
	done
done

