#!/usr/bin/env bash

BENCH_DIR=/home/vhui/ResearchCode/CC2_examples/NewReveInstances/libc
CLEVER_BIN=/home/vhui/ResearchCode/CC2New/CC2/CC2/checker_simple.py
REVE_BIN=/home/vhui/ResearchCode/llreve/reve/build/reve/llreve
Z3_450_BIN=/home/vhui/ResearchCode/z3-reve/z3-4.5.0-x64-ubuntu-14.04/bin/z3

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
    echo "${file}"
    echo "${filename}"
    echo "${clientname}"
    echo "${libname}"
    if [[ "$filename" =~ swab|strncasecmp_1|memrchr_1 ]] #if [ "$filename" = "swab" ] |strncasecmp_1 
    then
        echo "skipping"
    else
	echo "python3 ${CLEVER_BIN} --engine=reve --old=${filepath}_1.c --new=${filepath}_2.c --lib=${libname} --client=${clientname} &> ${filename}.out"	
	mkdir -p ${filename} && cd ${filename}
	#python3 ${CLEVER_BIN} --engine=reve --old="${filepath}_1.c" --new="${filepath}_2.c" --lib=${libname} --client=${clientname} &> ${filename}.out
	runlim --output-file=${filename}.runlim -t 600 -s 10000 python3 ${CLEVER_BIN} --engine=reve --old="${filepath}_1.c" --new="${filepath}_2.c" --lib=${libname} --client=${clientname} &> ${filename}.out
	cd ..
	#runlim --output-file=${filename}.runlim -t 600 -s 10000 ${REVE_BIN} -fun=${clientname} -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz ${filepath}_1.c ${filepath}_2.c &> ${filename}.reve
 	#set +e && runlim --output-file=${filename}.z3runlim -t 600 -s 10000 ${Z3_450_BIN} -smt2 fixedpoint.engine=duality ${filename}.smt2 &> ${filename}.outZ3 && set -e
    fi
done
cd ..
