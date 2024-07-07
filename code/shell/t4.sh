#!/bin/bash

file="hello.txt"
#这里使用了{}做了边界区
echo "this is ${file}name"

#这里因为没加{}把filename当做一个变量了
echo "this is $filename"

echo '测试单引号中使用的变量值 $file'
