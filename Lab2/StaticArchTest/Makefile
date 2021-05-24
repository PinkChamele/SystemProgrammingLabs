binary: main.o lib.a
	g++ -o binary main.o -L. -ltest
main.o: main.cpp
	g++ -c main.cpp
lib.a: MalfunctionType.o Database.o UserInterface.o
	ar cr libtest.a MalfunctionType.o Database.o UserInterface.o
UserInterface.o: UserInterface.cpp
	g++ -c UserInterface.cpp
Database.o: Database.cpp
	g++ -c Database.cpp
MalfunctionType.o: MalfunctionType.cpp
	g++ -c MalfunctionType.cpp
clean:
	rm -f *.o *.a binary
