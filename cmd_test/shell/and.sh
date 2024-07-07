#!/bin/bash

val=$1
#val=""
echo "输入的是：$val"

if [ -e "$val" ]; then
    echo "测试文件/目录 $val 存在"

    if [ -f $val ]; then
        echo "文件"
    elif [ -d $val ]; then
        echo "目录"
    else
        echo "输入了个啥"
    fi

else
    echo "测试文件/目录 $val bu存在"
fi
