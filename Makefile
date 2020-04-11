all: mainfile.cpp allclasses.h helperfunctions.h
	g++ -fPIC -c mainfile.cpp
	g++ -c mainfile.cpp -lm
	g++ -o main p.o -lm
	sudo ldconfig
	rm -rf *.o
