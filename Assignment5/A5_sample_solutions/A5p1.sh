#!/bin/bash

for arg in "$@"
do
	echo "$arg"
done

echo After sorting in numerical order:

if [ $# -eq 1 ]; then
	echo $1
elif [ $# -eq 2 ]; then
	if [[ $1 -lt $2 ]]
	then
		echo $1
		echo $2
	else
		echo $2
		echo $1
	fi
elif [ $# -eq 3 ]; then #clumsy sorting of three command line strings without using arrays, but it works
	if [[ $1 -lt $2 ]]
	then
		if [[ $3 -lt $1 ]]
		then
			echo $3
			echo $1
			echo $2
		elif [[ $3 -lt $2 ]]
		then
			echo $1
			echo $3
			echo $2
		else
			echo $1
			echo $2
			echo $3
		fi
	else #$1 > $2
		if [[ $3 -lt $2 ]]
		then
			echo $3
			echo $2
			echo $1
		elif [[ $3 -lt $1 ]]
		then
			echo $2
			echo $3
			echo $1
		else
			echo $2
			echo $1
			echo $3
		fi
	fi
else
	echo
fi
