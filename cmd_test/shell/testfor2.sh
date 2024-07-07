#!/bin/bash

list="aaa bbb ccc ddd"

for test in $list ; do
    echo "the next val is $test"
done

echo "--------------"

IFS=$'\n'
file="file"
for test in $( cat $file ) ; do
    echo "next world is : $test"
done


