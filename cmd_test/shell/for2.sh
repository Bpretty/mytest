#!/bin/bash

val="a b c d";
for test in $val; do
    echo "本次值: $test"
done

echo "---添加字符串hello后---"
val=$val" hello"

for test in $val; do
    echo "本次值: $test"
done


