dijkstra.out: dijkstra.o heap.o hash.o graph.o
	g++ -std=c++11 -o dijkstra.out dijkstra.o heap.o hash.o graph.o

dijkstra.o: dijkstra.cpp
	g++ -c -std=c++11 dijkstra.cpp

heap.o: heap.cpp heap.hpp
	g++ -c -std=c++11 heap.cpp

hash.o: hash.cpp hash.hpp
	g++ -c -std=c++11 hash.cpp

graph.o: graph.cpp graph.hpp
	g++ -c -std=c++11 graph.cpp

debug:
	g++ -std=c++11 -g -o dijkstra.out dijkstra.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups