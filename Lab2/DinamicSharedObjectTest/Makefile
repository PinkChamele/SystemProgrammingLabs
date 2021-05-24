binary: main.o lib.a
	g++ -o binary main.o -L. -ltest -Wl,--rpath -Wl,.
main.o: main.cpp
	g++ -c main.cpp
lib.a: MalfunctionType.o Database.o UserInterface.o
	g++ -shared -o libtest.so MalfunctionType.o Database.o UserInterface.o
UserInterface.o: UserInterface.cpp
	g++ -c -fPIC UserInterface.cpp
Database.o: Database.cpp
	g++ -c -fPIC Database.cpp
MalfunctionType.o: MalfunctionType.cpp
	g++ -c -fPIC MalfunctionType.cpp
clean:
	rm -f*.o *.a binary
