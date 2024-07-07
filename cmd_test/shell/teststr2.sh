#!/bin/bash

str1="val1"
str2="val2"

if [[ $str1 == v* ]]
then
    echo "hello1 $str1"
else
    echo "world1 $str1"
fi

if [[ $str1 == f* ]]
then
    echo "hello2 $str1"
else
    echo "world2 $str1"
fi
