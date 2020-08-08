#!/bin/bash

gnuplot <<- EOF
	set xlabel "Ano de evasao"
	set ylabel "Numero de evasoes"
	set title "Evasao por ano"
	set term png
	set output "./evasao/tabela1.png"
	plot 'tabela1.txt' with lines
EOF