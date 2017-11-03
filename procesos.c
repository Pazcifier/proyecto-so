#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

void AsignarLineas(int n, int cont, int *lineas);
void CrearPoH(int n);
void VerificarPrimo();

int main() {

  int n = 0;  //Cantidad de procesos/hilos
  int cont = 0; //Cantidad de líneas en el archivo
  int lineas = 0; //Las lineas con la que le toca trabajar
  int *apLineas = &lineas; //Apuntador a lineas (para referenciación)

  CrearPoH(n);
  AsignarLineas(n, cont, apLineas);

}

void AsignarLineas(int n, int cont, int *lineas) {
  if(fork() == 0) {
    *lineas = cont%n; //Lo que tiene que contar un hijo
  } else {
    *lineas = cont/n + cont%n; //Lo que tiene que contar el padre
  }
}

void CrearPoH(int n) {
  for(int i = 0; i < n; i++) {  //Creación de procesos/hilos
    if (fork() == 0)
      break;
  }

  printf("Soy un proceso\n");

}

void VerificarPrimo() {

}
