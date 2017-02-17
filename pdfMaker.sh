#!/bin/sh

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

if [ -d "include" ]
then
	for i in include/*.h
	do
			echo "Making PDF of $i"
			q=$(basename $i .h)
			a2ps --user-option=lp --borders=no --pretty-print=gnuc --landscape $i | ps2pdf - PDFs/include/$q.pdf
	done
fi

if [ -d "src" ]
then
	for i in src/*.c
	do
			echo "Making PDF of $i"
			q=$(basename $i .c)
			a2ps --user-option=lp --borders=no --pretty-print=gnuc --landscape $i | ps2pdf - PDFs/src/$q.pdf
	done
fi
