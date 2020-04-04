#!/bin/bash

for i in {1..3}
	do
	for j in {1..5}
		do
			((v = $i*$j)) #arithmetic context (( ))
			echo "$i * $j = $v"
		done
	done
