#!/bin/bash

play () {
	if [ $1 -eq 1 ]; then
		echo "$1"
	elif (( $1 % 2 )); then
		echo "$1 "
		play $(($1 * 3 + 1))
	else
		echo "$1 "
		play $(($1 / 2))
	fi
}

#check number of arguments
if [ "$#" != 1 ];
then
        echo "This script only accepts 1 argument" >&2; exit 1
fi

#check to make sure argument is integer
re='^[0-9]+$'
for arg in "$@"
do
        if ! [[ $arg =~ $re ]]; then
                echo "$arg is not a number" >&2; exit 1
        fi
done

#check to make sure argumet is between 50 & 100
if [ "$1" -lt 1 ] || [ "$1" -gt 50 ]; then
    echo 'error (out of range)' >&2
    exit 1
fi

play $1
