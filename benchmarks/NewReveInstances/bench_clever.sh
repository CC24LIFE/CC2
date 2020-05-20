#!/usr/bin/env bash

BENCH_DIR=/home/vhui/ResearchCode/CC2_examples/NewReveInstances/libc
CLEVER_BIN=/home/vhui/ResearchCode/CC2New/CC2/CC2/checker_simple.py
CLEVER_DIR=/home/vhui/ResearchCode/CC2New/CC2/CC2
REVE_BIN=/home/vhui/ResearchCode/llreve/reve/build/reve/llreve
Z3_450_BIN=/home/vhui/ResearchCode/z3-reve/z3-4.5.0-x64-ubuntu-14.04/bin/z3
Z3_487_BIN=/home/vhui/ResearchCode/z3-reve/z3-4.8.7-x64-ubuntu-16.04/bin/z3

#set -e
timestamp="$(date +"%Y-%m-%d_%H-%M-%S")"
mkdir -p clever-${timestamp}
cd clever-${timestamp}
for file in ${BENCH_DIR}/*_1.c
do
    filepath=${file:0:-4}
    fullfilename=`basename $filepath`
    clientname="$(cut -d'-' -f1 <<< ${fullfilename})"
    filename="$(cut -d'-' -f2 <<< ${fullfilename})"
    libname=${filename%_[0-9a-z]}
    #echo "${file}"
    #echo "${filename}"
    #echo "${clientname}"
    #echo "${libname}"
    if [[ "$filename" =~ swab|memrchr_1|strncasecmp_1|memmove_1|memset_1|memmem_1|strchr_2 ]] #strcspn$ #memrchr_1 #if [ "$filename" = "swab" ] |strncasecmp_1 
    then
        echo "skipping"
    else
	#echo "python3 ${CLEVER_DIR}/checker_simple.py --engine=reve --old=${filepath}_1.c --new=${filepath}_2.c --lib=${libname} --client=${clientname} &> ${filename}.out"	
	mkdir -p ${filename} && cd ${filename}
	#python3 ${CLEVER_BIN} --engine=reve --old="${filepath}_1.c" --new="${filepath}_2.c" --lib=${libname} --client=${clientname} &> ${filename}.out
	runlim --output-file=${filename}.runlim -t 300 -s 10000 python3 CC2 --old="${filepath}_1.c" --new="${filepath}_2.c" --lib=${libname} --client=${clientname} &> ${filename}.out 
	runlim --output-file=${filename}.Checkrunlim -t 300 -s 10000 python3 ${CLEVER_DIR}/check_reve.py --clientname="verify_this" --dir="$(pwd)" &> ${filename}.outreve
	parse_time=$(grep "time:" ${filename}.runlim | tr -dc '0-9'+'.')
	check_time=$(grep "time:" ${filename}.Checkrunlim | tr -dc '0-9'+'.')
	total_expr=$(echo "${parse_time} + ${check_time}")
	echo "./${filepath:37}: "equiv", $(echo ${total_expr} | bc);"	
	cd ..
    fi
done
cd ..
