$(shell mkdir -p bin)

Mmn22:	bin/main.o bin/complex.o
		gcc -g -Wall -ansi -std=c99 -pedantic bin/main.o bin/complex.o -o Mmn22 -lm

bin/complex.o:	complex.c compleX.h
			gcc -c -Wall -ansi -std=c99 -pedantic complex.c -o bin/complex.o

bin/main.o:	main.c common.h
			gcc -c -Wall -ansi -std=c99 -pedantic ./main.c -o bin/main.o

