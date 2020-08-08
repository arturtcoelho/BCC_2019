#!/bin/bash

cd /home/bcc/
# finger * | grep Name | cut -d: -f3 | cut -d' ' -f2 | sort -u > ~/nome_de_informatas.txt
finger * | grep Name | cut -d: -f3 > ~/nome_de_informatas.txt
cd -
