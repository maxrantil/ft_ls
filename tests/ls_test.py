#!/usr/local/bin/python3

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ls_test.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 16:46:13 by spuustin          #+#    #+#              #
#    Updated: 2022/09/05 18:01:46 by spuustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys, os, stat, filecmp
#from tkinter import READABLE

# HOW TO:
# run on command line: 
# python3 ls_test.py <path of ls_project>

# creating setuid/setgid/stickybit -testfiles,
# and a directory with no permissions
def create_files(path):
	files = {"/uidi": 0o2775, "/uidiS": 0o2666, "/gidi": 0o4775, "/gidiS": 0o4666, 
			"/sticky": 0o1775, "/stickyT": 0o1666}

	for name in files:
		f = open(path + name, "x")
		os.chmod(path + name, files[name])
		f.close()
	os.mkdir(path + "/noperm")
	# os.chmod(path + "/noperm", 000)

# running 'ls -l for files in project directory'
# comparing results
def write_to_files(path):
	os.system("ls> real.txt")
	os.system("./ft_ls> temp.txt")
	temp = open("temp.txt", "r+")
	real = open("real.txt", "r+")
	user = open("user.txt", "r+")
	for row in temp:
		x = row.split()
	for w in x:
		user.write(w + "\n")
	user.close()
	u = open("user.txt", "r")
	for line1 in u:
		for line2 in real:
			if line1 == line2:
				print("theyre the same")
			else:
				print("theyre different")
			break


if len(sys.argv) != 2:
	print("exactly one argument needed!\ntry 'python3 ls_test.py <path_of_dir>'")
else:
	path = sys.argv[1]
	# create_files(path)
	write_to_files(path)