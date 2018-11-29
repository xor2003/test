#!/bin/sh

rm *.out
i=1
while [ -r $i.dat ];
do 
	echo "~ Test $i";
	./_task2.exe $i.dat $i.out || exit $?
	test -r $i.out || (echo "Failed read $i.out"; exit 2;)
	test -r $i.bmk || (echo "Failed read $i.bmk"; exit 3;)
	diff -q $i.out $i.bmk || (echo "Failed $i"; exit 1;)
	i=$(( $i + 1 )); 
done
rm *.out
