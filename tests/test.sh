#!/bin/bash

.././ft_ls /.file 2>&1 | tee test_file.txt
read -p test_file.txt VAR1
read -p "./file" VAR2

if [[ "$VAR1" == "$VAR2" ]]; then
    echo "Strings are equal."
else
    echo "Strings are not equal."
fi