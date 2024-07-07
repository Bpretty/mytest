#!/bin/bash

#参数信
echo "参数个数 $#"

echo '--------------------------'
for i in "$*";do
    echo $i
done

echo '--------------------------'
for i in "$@";do
    echo $i
done

echo '--------------------------'
value=(a b c d)
for i in ${value[*]};do
    echo '获取值：'$i' ;'
done
