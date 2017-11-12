all:
	gcc -o primos primos.c -pthread
	gcc -o primosn primosn.c -pthread
	gcc -o semaforos semaforos.c -pthread
