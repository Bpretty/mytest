#!/bin/bash

#list=/home/ly/*
#for test in $list ; do
#    if [ -d $test ] ; then
#        echo "this is dir : $test"
#    else 
#        echo "this is file : $test"
#    fi
#done

#for test in  /home/ly/*  ; do
#    if [ -d "$test" ] ; then
#        echo "this is dir : $test"
#    else 
#        echo "this is file : $test"
#    fi
#done

for test in  *  ; do
    if [ -d "$test" ] ; then
        echo "this is dir : $test"
    else 
        echo "this is file : $test"
    fi

   if [[ $test == f* ]] ; then 
       echo "找到f开头的文件目录: $test"
   fi
done

