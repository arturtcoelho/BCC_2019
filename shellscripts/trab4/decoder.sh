#!/bin/bash

NUMLINHAS=$(wc -l $1 | cut -d ' ' -f1)

for linha in $(seq 1 $NUMLINHAS) ;do
	echo $(head -n $linha $1 | tail -n 1) > temp.txt
	STRING=$(cut -d = -f2 temp.txt | cut -d ')' -f1)
	echo "$STRING" | sed -r 's/[j]+/ /g' > temp.txt
#	cat temp.txt
	WORDS=$(wc -w temp.txt | cut -d ' ' -f1)
	for palavra in $(seq 2 $WORDS) ;do
		echo $(cut -d ' ' -f$palavra temp.txt) >> lista.txt
	done
done
sort lista.txt
sort lista.txt | uniq -c | sort

rm temp.txt lista.txt
