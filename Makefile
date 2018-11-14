
prog:	main.o ring.o
	cc -o prog main.o ring.o

main.o: main.c ring.h
	cc -c main.c

ring.o: ring.c ring.h
	cc -c ring.c

clean:  
	rm prog *.o

test: prog testfile
	./prog < testfile

