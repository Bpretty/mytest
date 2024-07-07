#!/bin/bash

val=$1
echo "输入的是：$val"
  
if [ -s "$val" ]; then  
    echo "$val 是一个非空文件1111"  
fi

# 检查文件是否存在且是一个普通文件  
if [ -f "$val" ]; then  
    # 检查文件是否非空  
    if [ -s "$val" ]; then  
        echo "$val 是一个非空文件"  
    else  
        echo "$val 是一个空文件"  
    fi  
else  
    echo "$val 不存在或不是一个普通文件"  
fi
