#!/bin/bash
#you can call this script with "bash A5p5.sh Collatz"
#where Collatz is the first command line argument for this script
#that serves as name of the C/C++ program to be launched
if [ -z $1 ]; then
	echo "usage: " $0 "<your_Cpp_Program>"
	exit
fi

for i in {26..30}
	do
		echo "sequence for $i"
		#call our C++ program $1 with one command line argument i
		./$1 $i #you may replace (hardcode) $1 with your C++ program name here; in this way you do not need to supply a command line argument to this script
		echo
	done
