spell.out: spellCheck.o hash.o
	g++ -std=c++17 -o spell.out spellcheck.o hash.o

spellCheck.o: spellCheck.cpp hash.hpp
	g++ -std=c++17 -c spellCheck.cpp

hash.o: hash.cpp hash.hpp
	g++ -std=c++17 -c hash.cpp

debug:
	g++ -std=c++17 -g -o spellDebug.out spellCheck.cpp hash.cpp

clean:
	rm -f *.exe *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups

