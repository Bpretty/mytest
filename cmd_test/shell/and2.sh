#!/bin/bash

val=$1
#val=""
echo "输入的是：$val"

if [ -f "$val" ]; then
        echo "文件"
elif [ -d "$val" ]; then
        echo "目录"
else
        echo "输入了个啥"
fi


