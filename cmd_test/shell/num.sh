#!/bin/bash

n1=4
n2=2
n3=$(expr $n1 / $n2)
n4=`expr $n1 + $n2`
echo "rst1 = $n3"
echo "rst2 = $n4"
