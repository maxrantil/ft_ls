#!/bin/bash

.././ft_ls /.file 2>&1 | tee test_file.txt
$VAR1 = $(cat test_file.txt)
$VAR2 = "./file"

if [[ "$VAR1" == "$VAR2" ]]; then
    echo "Strings are equal."
else
    echo "Strings are not equal."
fi


./ft_ls Makefile ../ft_printf/src/print_null_float_oct.c (print full path here)