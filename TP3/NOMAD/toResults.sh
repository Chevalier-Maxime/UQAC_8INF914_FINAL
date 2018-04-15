#!/bin/bash

_now=$(date +"%m_%d_%Y_%H_%M_%S")
_file="./resultats_finaux_$_now.txt"
_filePretty="./pretty_resultats_finaux_$_now.csv"
for filename in ./results/*_*_*.txt; do
    OLDIFS=$IFS
    IFS=" "

    read Qtot ElevAmont < $filename
    IFS=$OLDIFS

    BEST=$(grep "best feasible solution" $filename)
    BEST_INFEASIBLE=$(grep "best infeasible solution" $filename)

    if [[ $BEST = *no* ]]; then
	#Il n'y a pas de BEST solution
	Qs=$(cut -d ':' -f2 <<<"$BEST_INFEASIBLE")
	isReal="false"
    else
	Qs=$(cut -d ':' -f2 <<<"$BEST")
	isReal="true"
    fi
    
	QsValues=$(cut -d ')' -f1 <<<"$Qs")
	QsValues=$(cut -d '(' -f2 <<<"$QsValues")
	echo -n $QsValues >> $_file
	
	QsObj=$(cut -d ')' -f2 <<<"$Qs")
	QsReste=$(cut -d '=' -f2 <<<"$QsObj")
	QsReste=$(cut -d ' ' -f1 <<<"$QsReste")
	QsObj=$(cut -d '=' -f3 <<<"$QsObj")
	QsObj=$(cut -d '-' -f2 <<<"$QsObj")
	
	echo " $QsObj $QsReste $isReal" >> $_file

	
done

$(tr ' ' ';' <$_file >$_filePretty)
$(sed -i 's/$/;/' $_filePretty)
