#!/bin/bash

str1="val1"
str2="val2"
if [ $str1 == $str2 ]; then
    echo "equal"
else
    echo "not equal"
fi

if [ $str1 \> $str2 ]; then #这里使用必须转义
    echo "big str"
else
    echo "little str"
fi
