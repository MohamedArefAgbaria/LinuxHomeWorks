CC=gcc
all:
	$(CC) -shared -fPIC Utilities.c -o libUtilities.so
	$(CC) printdb.c -L`pwd` -lUtilities -o printdb.out
	$(CC) dbtocsv.c -L`pwd` -lUtilities -o dbtocsv.out
	$(CC) printblock.c -L`pwd` -lUtilities -o printblock.out
	$(CC) -o reload.out reloadDataBase.c
clean:
	rm -rf *.out *.so
