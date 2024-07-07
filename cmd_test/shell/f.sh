#!/bin/bash

val="roll"
  
if [[ $val == r* ]]; then
    echo "匹配到r开头的字符串了"
else
    echo "没有匹配到r开头的字符串"
fi
