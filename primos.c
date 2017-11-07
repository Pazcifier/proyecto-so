#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct hilos_primos {
  int lineas;
  int nroHilo;
  int primos;
  FILE *archivo;
};

int VerificarPrimo(int num);
int numLineas(FILE *fp);
int lineaToInt(FILE *fp);
void *salidaPrimoHilos (void* arg);

int main(int argc, char const *argv[]) {

  FILE *fp;
  int n = atoi(argv[4]);
  pthread_t hilos[n];
  struct hilos_primos hp[n];
  int primosTotal = 0;
  int cont = 0; //Cantidad de líneas en el archivo
  int lineasTrabajador = 0; //Lineas asignadas al trabajador
  int lineasTrabajadorUltimo = 0; //Lineas asignadas al maestro
  clock_t comienzo, fin; //Variables para tomar tiempo de ejecución
  double tiempo_cpu; //Usado para calcular el tiempo final

  fp=fopen(argv[1],"r");
  if (fp==NULL) {fputs ("File error",stderr); exit (1);
  } else {
    cont = numLineas(fp);
    rewind(fp);
    lineasTrabajador = cont/n;
    lineasTrabajadorUltimo = cont%n + cont/n;

    if (strcmp(argv[2], "-h") == 0) {
      for(int i = 0; i < n; i++) {
        hp[i].archivo = fp;
        hp[i].nroHilo = i;
        hp[i].primos = 0;

        if (i == (n - 1)) {
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
      for (int i = 0; i < n; i++) {
        primosTotal += hp[i].primos;
      }
    }
    printf("Cantidad total de primos: %d\n", primosTotal);
  }
  return 0;
}

void *salidaPrimoHilos (void* arg){
    struct hilos_primos *hp = (struct hilos_primos *) arg;

    int lineaInt;
    FILE *salida;
    char texto[10];
    char lineaS[20];
    sprintf(texto, "%d.txt", hp->nroHilo);

    for (int j = 0;j< hp->lineas; j++){
      lineaInt=lineaToInt(hp->archivo);
      if (VerificarPrimo(lineaInt) == 1) {
        hp->primos += 1;
      }
      sprintf(lineaS,"%d %d",lineaInt,VerificarPrimo(lineaInt));
      fprintf(salida, "%s \n",lineaS);
    }
    fclose(salida);
    pthread_exit(0);
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
