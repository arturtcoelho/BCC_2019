#!/bin/bash
NOME=$(basename -s .sh $0).bkp
cat $0 > $NOME