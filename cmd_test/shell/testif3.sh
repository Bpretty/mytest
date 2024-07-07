#!/bin/bash

if (( 5*1 )) ; then
    echo "num succ"
else
    echo "num fail"
fi

if (( 0 )) ; then
    echo "num succ"
else
    echo "num fail"
fi
