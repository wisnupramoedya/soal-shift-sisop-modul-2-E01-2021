#!/bin/bash
myarr=($(ps aux | grep './soal3' | awk '{ print $2 }'))

if [[ $1 = "-z" ]]
then
    # echo "-z"
    for i in "${myarr[@]}"
    do
        kill -9 $i
    done
elif [[ $1 = "-x" ]]
then
    # echo "-x"
    kill -9 ${myarr[0]}
fi