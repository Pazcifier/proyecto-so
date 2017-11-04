#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int VerificarPrimo(int num);
int numLineas(FILE *fp);
int lineaToInt(FILE *fp);
void salidaPrimo ( int lineasT, int i, FILE *fp);

int main(int argc, char const *argv[]) {

  FILE *fp; //Variable para leer el archivo
  int n = atoi(argv[4]);  //Cantidad de procesos/hilos trabajadores
  int cont = 0; //Cantidad de líneas en el archivo
  int lineasTrabajador = 0; //Lineas asignadas al trabajador
  int lineasTrabajadorUltimo = 0; //Lineas asignadas al maestro


  fp=fopen(argv[1],"r");
  if (fp==NULL) {fputs ("File error",stderr); exit (1);
  } else {
      cont = numLineas(fp);
      rewind(fp);
      lineasTrabajador = cont/n;
      lineasTrabajadorUltimo = cont%n + cont/n;
      for(int i = 0; i < n; i++) {
        if (fork() == 0) {
          break;
        }
        salidaPrimo(lineasTrabajador, i, fp);
      }
  }
  fclose ( fp );

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

    for (int j; j<lineasT; j++){
      lineaInt=lineaToInt(fp);
      //primo=VerificarPrimo(lineaInt);
      sprintf(lineaS,"%d %d",lineaInt,VerificarPrimo(lineaInt));
      //printf("%s \n",lineaS);
      //printf("%d \n",lineaToInt(fp));

    }
    fclose(salida);
}
