#!/bin/bash
echo
#[ITEM1]
ARQTAR=$1
tar -xzf $ARQTAR -C .

#[ITEM2]
ARQSEVASAO=$(ls evasao)
echo "[ITEM 3]" ; echo
echo "RANKING DE EVASAO DE 2014-2018"
for arquivo in $ARQSEVASAO ;do
	cat ./evasao/$arquivo >> todos_os_arquivos.txt
done

#[ITEM3]
cut -d , -f1 todos_os_arquivos.txt | sed '/FORMA_EVASAO/d' | sort | uniq -c | sort -nr
echo

#rankings por ano
#for arquivo in $ARQSEVASAO ;do
#	ANO=$(echo $arquivo | cut -d '-' -f2 | cut -d . -f1)
#	echo "RANKING DE EVASAO DE $ANO"
#	cut -d , -f1 ./evasao/$arquivo | sed '/FORMA_EVASAO/d' | sort | uniq -c | sort -nr
#	echo
#done

#[ITEM4]
echo "[ITEM 4]" ;echo
for arquivo in $ARQSEVASAO ;do
	EGRESSO=$(echo $arquivo | cut -d '-' -f2 | cut -d . -f1)
	sed '/ANO_INGRESSO/d' ./evasao/$arquivo | cut -d , -f4 > ./evasao/ingresso$EGRESSO
	while read ingresso; do
		echo $(expr $EGRESSO - $ingresso) >> anos_de_permanencia.txt
	done < ./evasao/ingresso$EGRESSO
	rm ./evasao/ingresso$EGRESSO
done
sort -n anos_de_permanencia.txt | uniq -c | sed '1s/^/ALUNOS\tANOS\n/'

rm anos_de_permanencia.txt 

#[ITEM5]
echo ;echo "[ITEM 5]"
for arquivo in $ARQSEVASAO ;do
	ANO=$(echo $arquivo | cut -d '-' -f2 | cut -d . -f1)
	echo; echo "PORCENTAGENS PARA $ANO"
	tail -n +2 ./evasao/$arquivo | cut -d , -f2 | sort | uniq -c | cut -d ' ' -f6 > tempsemestres.txt
	SEM1=$(head -n 1 tempsemestres.txt)
	SEM2=$(tail -n 1 tempsemestres.txt)
	TOTAL=$(expr $SEM1 + $SEM2)
	if [ "$SEM1" -gt "$SEM2" ] ;then
		echo semestre 1 $(bc -l <<< "$SEM1 / $TOTAL * 100" | cut -b -5)%
	else
		echo semestre 2 $(bc -l <<< "$SEM2 / $TOTAL * 100" | cut -b -5)%
	fi
done
rm tempsemestres.txt

#[ITEM6]
echo; echo "[ITEM 6]"  
sed -i '/SEXO/d' ./todos_os_arquivos.txt
cut -d , -f5 todos_os_arquivos.txt | sort | uniq -c | tail -n 2 | sed 's/\([^ ]*\) *\(.*\)/\2 \1/' | cut -d ' ' -f1 > generos.txt
FEMININO=$(head -n 1 generos.txt)
MASCULINO=$(tail -n 1 generos.txt)
TOTAL=$(expr $FEMININO + $MASCULINO)
echo SEXO$'\t'"MEDIA EVASOES"
echo F$'\t'$(bc -l <<< "$FEMININO / $TOTAL * 100" | cut -b -5)%
echo M$'\t'$(bc -l <<< "$MASCULINO / $TOTAL * 100" | cut -b -5)%
rm generos.txt
echo

#[ITEM 7]
for ano in $ARQSEVASAO ;do
	ANO=$(echo $ano | cut -d '-' -f2 | cut -d . -f1)
	ALUNOS=$(wc -l ./evasao/$ano | cut -d ' ' -f1)
	echo $ANO$'\t'$(($ALUNOS - 1)) >> tabela1.txt
done

gnuplot <<- EOF
	set xlabel "Ano de evasao"
	set ylabel "Numero de evasoes"
	set title "Evasao por ano"
	set term png
	set output "evasoes-ano.png"
	plot 'tabela1.txt' with lines
EOF
	#	salvar o grafico na pasta interfere na proxima execucao do script,
	#	nos itens 3,4,5 e 6 sao usados todos os arquivos do diretorio 'evasao'
rm tabela1.txt
#rm ./evasao/tabela1.png

#[ITEM8]
echo \# $(cut -d , -f3 ./todos_os_arquivos.txt | awk '{ print "\""$0"\""}' | sed '/FORMA_INGRESSO/d' | sort | uniq | tr '\n' ' ') >> tabela2.txt
for ano in $ARQSEVASAO; do
	cut -d , -f3 ./todos_os_arquivos.txt | sed '/FORMA_INGRESSO/d' | sort | uniq | sed 's/^/,,/' >> ./evasao/$ano
	ANO=$(echo $ano | cut -d '-' -f2 | cut -d . -f1)
	echo $ANO $(cut -d , -f3 ./evasao/$ano | sed '/FORMA_INGRESSO/d' | sort | uniq -c | sed 's/\([^ ]*\) *\(.*\)/\2 \1/' | cut -d ' ' -f1 | while read line ;do echo $(( $line - 1 )); done | tr '\n' ' ') >> tabela2.txt
done

gnuplot << EOF
	set terminal png size 1200,700
	set output 'evasoes-forma.png'
	
	set style data histogram
	set style histogram cluster gap 1
	
	set yrange [0:100]
	set style fill solid
	set style fill solid border rgb 'black'
	set boxwidth 0.8
	set xtics format ""
	set grid ytics
	set title "Evasão por forma de ingresso entre 2014 e 2018"

	plot "tabela2.txt" using 2:xtic(1) title "Aluno Intercâmbio", \
		'' using 3 title "Aproveitamento Curso Superior", \
		'' using 4 title "Convênio AUGM", \
		'' using 5 title "Convênio Pec-G", \
		'' using 6 title "Mobilidade Acadêmica", \
		'' using 7 title "Processo Seletivo/ENEM", \
		'' using 8 title "Reopção", \
		'' using 9 title "Transferência Ex-Ofício", \
		'' using 10 title "Transferência Provar" linecolor 'pink', \
		'' using 11 title "Vestibular" linecolor 'skyblue'
EOF
rm tabela2.txt 

rm todos_os_arquivos.txt