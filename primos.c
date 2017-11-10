#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

struct hilos_primos {
  int lineas;
  int nroHilo;
  FILE *archivo;
};

int VerificarPrimo(int num);
int numLineas(FILE *fp);
int lineaToInt(FILE *fp);
void salidaPrimo ( int lineasT, int i, FILE *fp);
void *salidaPrimoHilos (void* arg);

int main(int argc, char const *argv[]) {

  FILE *fp; //Variable para leer el archivo
  int n = atoi(argv[4]); //Cantidad de procesos/hilos trabajadores
  pthread_t hilos[n]; //Vector de hilos trabajadores
  struct hilos_primos hp[n];
  int cont = 0; //Cantidad de líneas en el archivo
  int lineasTrabajador = 0; //Lineas asignadas al trabajador
  int lineasTrabajadorUltimo = 0; //Lineas asignadas al maestro
  clock_t comienzo, fin; //Variables para tomar tiempo de ejecución
  double tiempo_cpu; //Usado para calcular el tiempo final

  if ((n > 10) || (n < 1)) {
    printf("ERROR: Número de procesos/hilos debe estar entre 1 y 10\n");
    return 0;
  }

  fp=fopen(argv[1],"r");
  if (fp==NULL) {fputs ("File error",stderr); exit (1);
  } else {
      cont = numLineas(fp);
      rewind(fp);
      lineasTrabajador = cont/n;
      lineasTrabajadorUltimo = cont%n + cont/n;

      if (strcmp(argv[2], "-p") == 0) {
        comienzo = clock();
        for(int i = 0; i < n; i++) {
          if (fork == 0) {
            break;
          } else {
            if (i == (n-1)) {
              salidaPrimo(lineasTrabajadorUltimo, i, fp);
            } else {
              salidaPrimo(lineasTrabajador, i, fp);
            }
          }
        }
      } else if (strcmp(argv[2], "-h") == 0) {
        comienzo = clock();
        for(int i = 0; i < n; i++) {
          hp[i].archivo = fp;
          hp[i].nroHilo = i;
          if (i == (n-1)) {
            hp[i].lineas = lineasTrabajadorUltimo;
            pthread_create(&hilos[i], NULL, salidaPrimoHilos, &hp[i]);
          } else {
            hp[i].lineas = lineasTrabajador;
            pthread_create(&hilos[i], NULL, salidaPrimoHilos, &hp[i]);
          }
        }

       for(int i = 0; i < n; i++) {
          pthread_join(hilos[i], NULL);
        }
      }
      fin = clock();
      tiempo_cpu = ((double) (fin - comienzo)) / CLOCKS_PER_SEC;
      printf("Tiempo final de ejecución: %fs\n", tiempo_cpu);
 }
  return 0;
}

int numLineas(FILE *fp){
    const size_t tamlineas = 300;
    char *linea= malloc(tamlineas);
    int num=0;
    while(fgets(linea,tamlineas,fp)!= NULL){
        num++;
    }
    free(linea);
    return num;
}

int VerificarPrimo(int num){
    int i,a;
    a=0;
    for(i=1;i<=num;i++)
    {
        if(num%i==0) // si num módulo de i es 0, incrementamos a en 1.
        a++;
        if (a>2) break;
    }


    if(a==2){ //Si al final del bucle, a vale 2, el número es primo, porque tiene solamente 2 divisores
        return 1;
    }
        else
        {
        return 0;
        }
}

int lineaToInt(FILE *fp){
    const size_t tamlineas = 300;
    char *linea= malloc(tamlineas);
    int num=0;
    fgets(linea,tamlineas,fp);
    num = atoi(linea);
    return num;
}

void salidaPrimo ( int lineasT, int i, FILE *fp){
    int lineaInt;
    FILE *salida;
    char texto[10];
    char lineaS[20];
    sprintf(texto, "%d.txt", i);
    salida = fopen(texto,"w");

    for (int j=0;j<lineasT; j++){
      lineaInt=lineaToInt(fp);
      sprintf(lineaS,"%d %d",lineaInt,VerificarPrimo(lineaInt));
      fprintf(salida, "%s \n",lineaS);

    }
    fclose(salida);
}

void *salidaPrimoHilos (void* arg){
    struct hilos_primos *hp = (struct hilos_primos *) arg;

    int lineaInt;
    FILE *salida;
    char texto[10];
    char lineaS[20];
    sprintf(texto, "%d.txt", hp->nroHilo);
    salida = fopen(texto,"w");

    for (int j = 0;j< hp->lineas; j++){
      lineaInt=lineaToInt(hp->archivo);
      sprintf(lineaS,"%d %d",lineaInt,VerificarPrimo(lineaInt));
      fprintf(salida, "%s \n",lineaS);

    }
    fclose(salida);
    pthread_exit(0);
}
