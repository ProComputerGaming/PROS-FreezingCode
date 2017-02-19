#!/bin/sh

#Must be run in the root directory of your PROS Project
#Creates PDFs of all .c and .h files and places them in [project directory]/PDFs

#Requires the 'a2ps' and 'ps2pdf' packages

if [ -e "project.pros"]
then

	if [ -d "PDFs" ]
	then
		rm -r PDFs/*
		mkdir PDFs/src
		mkdir PDFs/include
	else
		mkdir PDFs
		mkdir PDFs/src
		mkdir PDFs/include
	fi

	#Make PDF's of .h files in the 'include' folder
	if [ -d "include" ]
	then
		for i in include/*.h
		do
			echo "Making PDF of $i"
			q=$(basename $i .h)
			a2ps --user-option=lp --borders=no --pretty-print=gnuc --landscape $i | ps2pdf - PDFs/include/$q.pdf
		done
	else
		echo "'include' directory not found. PDFs of header files won't be created"
	fi

	#Make PDF's of .c files in the 'src' folder
	if [ -d "src" ]
	then
		for i in src/*.c
		do
			echo "Making PDF of $i"
			q=$(basename $i .c)
			a2ps --user-option=lp --borders=no --pretty-print=gnuc --landscape $i | ps2pdf - PDFs/src/$q.pdf
		done
	else
		echo "'src' directory not found. PDFs of source files won't be created"
	fi
fi
