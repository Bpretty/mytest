#!/bin/bash

val="$1"
echo "输入了: $val"
  
case $val in 
    ly) 
        echo $val;;
    ly2 | ly3) 
        echo $val;;
    *) 
        echo other;;
esac
