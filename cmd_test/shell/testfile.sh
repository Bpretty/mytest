#!/bin/bash

if [ -d /home/11 ] || [ -d /home/ly ]
then
    echo "\$dir exit"
else
    echo "\$dir not exit"
fi

if [ -d /home/11 ] && [ -d /home/ly ]
then
    echo "|| dir exit"
else
    echo "|| dir not exit"
fi
