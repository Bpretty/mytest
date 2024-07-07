#!/bin/bash

val=$1
echo "输入的是：$val"

if [ "$val" -eq 1 ]; then
    echo hello1
elif [ "$val" -eq 2 ]; then
    echo hello2
else
    echo hello3
fi

#
#if [ "$val" -eq 1 ]; then
#    echo hello1
#elif [ "$val" -eq 2 ]; then
#    echo hello2
#else
#    echo hello3
#fi
