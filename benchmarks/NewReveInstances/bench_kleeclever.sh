#!/usr/bin/env bash

BENCH_DIR=/host/libc

set -e
timestamp="$(date +"%Y-%m-%d_%H-%M-%S")"
mkdir -p exp-${timestamp}
cd exp-${timestamp}
for file in ${BENCH_DIR}/*_1.c
do
    filepath=${file:0:-4}
    fullfilename=`basename $filepath`
    clientname="$(cut -d'-' -f1 <<< ${fullfilename})"
    filename="$(cut -d'-' -f2 <<< ${fullfilename})"
    libname=${filename%_[0-9]}
    if [[ "$filename" =~ swab|memrchr_1 ]] #if [ "$filename" = "swab" ] |strncasecmp_1 
    then
        echo "skipping"
    else
	#echo "${REVE_BIN} -fun=${clientname} -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz  ${filepath}_1.c ${filepath}_2.c && ${Z3_450_BIN} -smt2 fixedpoint.engine=duality \"${filename}.smt2\" "
	#echo "${REVE_BIN} -infer-marks -fun=${clientname} -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz  ${filepath}_1.c ${filepath}_2.c && ${Z3_450_BIN} -smt2 fixedpoint.engine=duality \"${filename}.smt2\" "
        #echo "${REVE_BIN} \"${filepath}_1.c\" \"${filepath}_2.c\" -o \"${filename}.smt2\" -resource-dir /usr/local/lib/clang/5.0.0/ -inline-opts && eld-client -t:300 \"${filename}.smt2\"" # >& /dev/null)
        #time (/bin/bash -c "${REVE_BIN} \"${filepath}_1.c\" \"${filepath}_2.c\" -o \"${filename}.smt2\" -resource-dir=/usr/lib/clang/6.0.0/ -inline-opts ") 
	#runlim --output-file=${filename}.runlim ${REVE_BIN} -fun=${clientname} -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz  ${filepath}_1.c ${filepath}_2.c &> ${filename}.reve 
	#runlim --output-file=${filename}.runlim -t 600 -s 10000 ${REVE_BIN} -fun=${clientname} -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz  ${filepath}_1.c ${filepath}_2.c &> ${filename}.reve && runlim --output-file=${filename}.z3runlim -t 600 -s 10000 ${Z3_450_BIN} -smt2 fixedpoint.engine=duality ${filename}.smt2 &> ${filename}.outZ3
	#set +e
	#runlim --output-file=${filename}.runlim -t 300 -s 10000 ${REVE_BIN} -fun=${clientname} -infer-marks -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz ${filepath}_1.c ${filepath}_2.c &> ${filename}.reve
	#set -e
	#set +e && /host/runlim-1.10/runlim --output-file=${filename}.runlim -t 200 -s 10000 CLEVERC --old ${filepath}_1.c --new ${filepath}_2.c --client ${clientname} --lib ${libname}
	CLEVERC --old ${filepath}_1.c --new ${filepath}_2.c --client ${clientname} --lib ${libname}
	ttime=$(grep "time:" ${filename}.runlim | tr -dc '0-9'+'.')
        echo "./${filepath:37}: "equiv", ${ttime};" 
    fi
done
cd ..
