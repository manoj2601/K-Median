all: mainfile.cpp allclasses.h
	g++ -o main mainfile.cpp
	rm -rf *.o

clean:
	rm -rf main costs.txt proxies.txt *.o
run:
	rm -rf costs.txt proxies.txt
	for NUM in `seq 1 1 10`; do ./main $$NUM; done;


