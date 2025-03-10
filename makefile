proj1.exe: main.o Cell.o Residential.o Commercial.o Industrial.o SimSystem.o Pollution.o
	g++ main.o Cell.o Residential.o Commercial.o Industrial.o SimSystem.o Pollution.o -o proj1.exe

main.o: main.cpp
	g++ -Wall -c main.cpp

Cell.o: Cell.h Cell.cpp
	g++ -Wall -c Cell.cpp

Residential.o: Residential.h Residential.cpp
	g++ -Wall -c Residential.cpp

Commercial.o: Commercial.h Commercial.cpp
	g++ -Wall -c Commercial.cpp

Industrial.o: Industrial.h Industrial.cpp
	g++ -Wall -c Industrial.cpp

SimSystem.o: SimSystem.h SimSystem.cpp
	g++ -Wall -c SimSystem.cpp

Pollution.o: Pollution.h Pollution.cpp
	g++ -Wall -c Pollution.cpp
clean:
	rm *.o proj1.exe

