shell: parse.o exec.o
	gcc main.c parse.o exec.o -o shell

all:
	gcc -Wall pwd.c -o pwd
	gcc -Wall echo.c -o echo
	gcc -Wall ls.c -o ls
	gcc -Wall pinfo.c -o pinfo

parse.o: parse.c parse.h
	gcc -c parse.c -o parse.o

exec.o: exec.c exec.h
	gcc -c exec.c -o exec.o

clean:
	rm shell pwd echo ls pinfo parse.o exec.o
