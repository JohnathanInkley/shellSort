execute: main.o shell.o
	g++ -g main.o shell.o -o execute

main.o: main.cpp shell.h
	g++ -g -c main.cpp

shell.o: shell.cpp shell.h
	g++ -g -c shell.cpp -o shell.o

clean:
	rm -f *.o execute
