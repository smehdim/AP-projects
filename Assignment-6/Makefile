CC := g++ --std=c++11

main: office.o doc.o main.o
	$(CC) office.o doc.o main.o -o permitMaker.out

main.o: main.cpp
	$(CC) -c main.cpp -o main.o
	
office.o: office.cpp office.hpp doc.hpp doc.hpp
	$(CC) -c office.cpp -o office.o

doc.o: doc.cpp doc.hpp
	$(CC) -c doc.cpp -o doc.o

clean:
	rm *.o



