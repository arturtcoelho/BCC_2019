#!/bin/bash
#o script recebe o codigo como argumento
#recebe o numero de linhas
NUMLINHAS=$(wc -l $1 | cut -d ' ' -f1)

for linha in $(seq 1 $NUMLINHAS) ;do
        echo $(head -n $linha $1 | tail -n 1) > temp.txt
#para cada linha
        STRING=$(cut -d = -f2 temp.txt | cut -d ')' -f1)
#corta a parte relevante da cripto        
        echo "$STRING" | sed -r 's/[j]+/ /g' > temp.txt
#substitui por espacos
        WORDS=$(wc -w temp.txt | cut -d ' ' -f1)
        for palavra in $(seq 2 $WORDS) ;do
                echo $(cut -d ' ' -f$palavra temp.txt) >> lista.txt
        done #enlista as letras
done
sort lista.txt | uniq -c | sort -nr
#retorna o numero de vezes que cada letra aparece

rm temp.txt lista.txt

