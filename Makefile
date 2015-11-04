solar:	Planetoid.o Universe.o main.o
	g++ Planetoid.o Universe.o main.o -o solar

Planetoid.o:	Planetoid.cpp Planetoid.h
	g++ -c Planetoid.cpp

Universe.o:	Universe.cpp Universe.h Planetoid.h
	g++ -c Universe.cpp

main.o:	main.cpp Universe.h Planetoid.h
	g++ -c main.cpp

clean:
	rm *o solar
