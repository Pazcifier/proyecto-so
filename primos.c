#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void AsignarLineas(int n, int cont, int *lineas);
void CrearPoH(int n);
void VerificarPrimo();

int main(int argc, char const *argv[]) {

  FILE *fp;
  int n = atoi(argv[4]);  //Cantidad de procesos/hilos
  int cont = 0; //Cantidad de líneas en el archivo
  int lineas = 0; //Las lineas con la que le toca trabajar
  int *apLineas = &lineas; //Apuntador a lineas (para referenciación)

  CrearPoH(n);
  if (fork() == 0) {
    fp = fopen(argv[1],"r");
    if (fp==NULL) {fputs ("File error",stderr); exit (1);
    } else {
        printf("Abrio ARCHIVO \n");
    }
    while(feof(fp) == 0) {
      cont++;
    }
    fclose(fp);
    printf("Cerro ARCHIVO\n");
  }

  printf("Contador de líneas: %d\n", cont);
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
