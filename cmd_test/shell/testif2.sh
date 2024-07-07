#!/bin/bash

val="hello"
if test $val; then
   echo "val succ"
else
    echo "val fail"
fi

val2=""
if test $val2; then
   echo "val2 succ"
else
    echo "val2 fail"
fi

if [ 1 ]; then
    echo "num succ"
else
    echo "num fail"
fi

if [ -d /home/11 ]; then
    echo "i am suc"
else
    echo "i am fail"
fi

echo "go end"
