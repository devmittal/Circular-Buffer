
vpath %.c src
vpath %.h inc

prog:	main.o ring.o
	cc -o prog main.o ring.o

main.o: main.c ring.h
	cc -c src/main.c

ring.o: ring.c ring.h
	cc -c src/ring.c

clean:  
	rm prog *.o

test: prog testfile
	./prog < testfile

