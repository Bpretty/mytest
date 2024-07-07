#!/bin/bash

a=(A B "c" D)
echo ${a[0]}
echo ${a[1]}
echo ${a[2]}
echo ${a[3]}

echo "---分界线----"

echo "${a[@]}"

echo "---分界线----"

echo "${a[*]}"
