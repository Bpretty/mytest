#!/bin/bash

for test in aaa bbb ccc ddd ; do
    echo "the next val is $test"

    if [ $test == "aaa" ] ; then
        echo "find aaa, and create new val t2"
        t2="my"
    fi
done

echo "循环完之后 tes 的值是: $test"
echo "循环完之后 t2 的值是: $t2"
test="hello"
echo "修改完成之后test的值为$test"

export test #测试发现这些符号父进程中并不可见
export t2 #测试发现这些符号父进程中并不可见
