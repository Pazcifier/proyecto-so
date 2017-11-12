all:
	gcc -o primos primos.c -pthread
	gcc -o primosn primosn.c -pthread
	gcc -o p4 problema4.c -pthread
