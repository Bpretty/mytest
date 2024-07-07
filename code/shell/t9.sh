#!/bin/bash

#关系运算符
v1=10
v2=20
value=`expr $v1 + $v2`
echo "相加得到：$value"
value=`expr $v1 \* $v2`
echo "相乘得到：$value"

if [ $v1 == $v2 ] 
then
    echo "两个值相等"
else
    echo "两个值不相等"
fi

echo -e "测试换行 \n" #需要加入-e开启转义

echo `date`
