#!/bin/bash
for i in {1..3}
do
	for j in {1..5}
	do
		echo "$i*$j=$((i*j))"
	done
done

