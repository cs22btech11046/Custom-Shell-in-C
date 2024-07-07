all : main.o ls.o cp.o mv.o grep.o
	gcc main.o ls.o cp.o mv.o grep.o -lreadline
main.o: main.c
	gcc -c main.c 
ls.o: ls.c
	gcc -c ls.c
cp.o: cp.c
	gcc -c cp.c
mv.o: mv.c
	gcc -c mv.c
grep.o: grep.c
	gcc -c grep.c
	
