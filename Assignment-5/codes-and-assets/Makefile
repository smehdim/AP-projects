CC := g++ --std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

doodlejump.out: main.o rsdl.o platform.o enemy.o doodle.o springs.o game.o consts.hpp
	$(CC) main.o rsdl.o platform.o enemy.o doodle.o springs.o game.o $(CCFLAGS) -o doodlejump.out

main.o:	main.cpp consts.hpp
	$(CC) -c main.cpp -o main.o

rsdl.o: rsdl.hpp rsdl.cpp consts.hpp
	$(CC) -c rsdl.cpp -o rsdl.o

platform.o: platform.cpp platform.hpp consts.hpp
	$(CC) -c platform.cpp -o platform.o

enemy.o: enemy.cpp enemy.hpp consts.hpp
	$(CC) -c enemy.cpp -o enemy.o

doodle.o: doodle.cpp doodle.hpp consts.hpp
	$(CC) -c doodle.cpp -o doodle.o

springs.o : spring.cpp springs.hpp consts.hpp
	$(CC) -c spring.cpp -o springs.o

game.o :game.cpp game.hpp consts.hpp
	$(CC) -c game.cpp -o game.o

clean:
	rm *.o