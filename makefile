main: main.o vector3d.o SDF.o
	g++ -Wall main.o vector3d.o SDF.o -o main

main.o: main.cpp vector3d.h SDF.h
	clear
	g++ -Wall -c main.cpp

vector3d.o: vector3d.cpp vector3d.h
	g++ -Wall -c vector3d.cpp

SDF.o: SDF.cpp SDF.h
	g++ -Wall -c SDF.cpp

clean:
	rm -f *.o main
