#!/bin/bash

#check number of arguments
if [ "$#" != 1 ];
then
	echo "This script only accepts 1 argument" >&2; exit 1
fi

#check to make sure arguments are integers
re='^[0-9]+$'
for arg in "$@"
do
	if ! [[ $arg =~ $re ]]; then
		echo "$arg is not a number" >&2; exit 1
	fi
done

for ((i = 0; i <= $1; i++ ))
do
	printf "%d " $i
done
