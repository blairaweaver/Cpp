#!/bin/bash
if [ $# -ne 1 ]; then
	echo "usage: " $0 "<n:1~50>"
	exit
fi

var=$1

if [[ $var -lt 1 || $var -gt 50 ]]; then
	echo "input integer should be between 1 and 50"
	exit
fi

printf "Here is your list:\n%d, " $var #printf is also available in bash, but its usage is not identical to those in C/Java
len=1 #optional variable to hold the number of printed integers
while [  $var -ne 1 ]; do
	#((r=var%2))
	let r=$var%2 #arithmetic operations with let; r is used to test whether var is even or odd
	if [ $r -eq 1 ]; then #update var according to whether var is even or odd
		let var=var*3+1 
	else
		let var=var/2 
	fi
	let len++
	printf "%d, " $var #we use printf here instead of echo so that the list can be printed on the same line
done
echo
echo "len=$len"
