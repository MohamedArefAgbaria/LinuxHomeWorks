all: libprint.so main main2 main3

libprint.so: lib.c
	gcc lib.c -shared -fpic -o libprint.so

main: Ex3Server.c lib.h
	gcc -pthread Ex3Server.c LinkedList.c -lz -lm -lrt -o server.out
main2: Ex3Miner.c lib.h
	gcc -pthread Ex3Miner.c -lz -lm -lrt -o miner.out 
main3: Ex3Launcher.c lib.h
	gcc -pthread Ex3Launcher.c -lz -lm -lrt -o launcher.out 

clean: 
	rm -rf *.out *.so
