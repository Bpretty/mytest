#!/bin/bash

#test不传命令时退出码为非0
if test 
then
    echo succ
else
    echo fail
fi

#test测试空字符时退出状态码也是非0
val=""
if test $val     #注意$val才能使用到变量的值
then
    echo succ2
else
    echo fail2
fi


val="hello"
if test $val    
then
    echo succ3
else
    echo fail3
fi


