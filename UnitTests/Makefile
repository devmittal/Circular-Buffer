
vpath %.c ../src
vpath %.h ../inc

unittest: unit_test.o ring.o
	  cc -o unittest unit_test.o ring.o -lcunit

unit_test.o: unit_test.c
	     cc -c unit_test.c

ring.o: ring.c ring.h
	cc -c ../src/ring.c

clean:
	rm unittest *.o
