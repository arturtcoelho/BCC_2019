#!/bin/bash

logger -is "Teste do comando logger" 2>> teste.txt
cd /var/log/
grep -s "Teste do comando logger" * | cut -d 'T' -f1
cd -