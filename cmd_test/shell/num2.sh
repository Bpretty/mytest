#!/bin/bash

n1=4
n2=2

n3=$[51 + $n2]
n4=$[$n1 / $n2]
n5=$[$n1 * $n2]

echo "rst1 = $n3"
echo "rst2 = $n4"
echo "rst3 = $n5"
