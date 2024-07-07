#!/bin/bash

#演示换成 \n 为分隔符
#IFS.OLD=$IFS
IFS_OLD=$IFS
IFS=$'\n'
for test in $( cat t.txt ); do
    echo "本次值: $test"
done

echo "---展示原始效果---"
#演示换回去之后的原始效果
IFS=$IFS_OLD
for test in $( cat t.txt ); do
    echo "本次值: $test"
done

