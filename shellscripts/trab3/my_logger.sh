#!/bin/bash

LOG=$1
DIRETORIO=$2
CARACTERISTICAS='info warn error'
DATE=$(date +"%d-%m-%Y")
#por algum motivo a variavel date nao funcionou na concatenacao
#por isso foi substituida pelo original
if [ ! -d $DIRETORIO ] ;then
	mkdir ./$DIRETORIO
fi
for i in $CARACTERISTICAS ; do
	grep $i $LOG >> ./$DIRETORIO/$(date +"%d-%m-%Y")_$i.log
done
tar -czf ./$DIRETORIO/logs.tar.gz ./$DIRETORIO/* 
if [ -a ./$DIRETORIO/logs.tar.gz ] ;then
	logger "Arquivo de log criado com sucesso"
else
	logger "Erro ao criar arquivos de log"
fi