#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


void Bicis(int a[], int type, FILE *fp);
int CuantasB(FILE *fp,int type);

int main(int argc, char const *argv[]){
	//sem_t *semI =sem_open("Izq",O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	//sem_t *semD =sem_open("Der",O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	int der=0;
	int izq=0;
	FILE *fp;
	fp=fopen(argv[1],"r");
	 if (fp==NULL) {fputs ("File error",stderr); exit (1);
  	} else {
  		izq = CuantasB(fp,0);
  		rewind(fp);
  		der = CuantasB(fp,1);
  		rewind(fp);
  		int BicisLeft[izq];
  		int BicisRight[der];
			int turnoLeft = 0;
			int turnoRight = 0;
  		Bicis(BicisLeft,0,fp);
  		rewind(fp);
  		Bicis(BicisRight,1,fp);

			printf("Bicis Right\n");
  		for (int i = 0; i < der; ++i)
  		  {
  		  	printf("%d\n",BicisRight[i] );
  		  }
  		printf("\n");

			printf("Bicis Left\n");
  		for (int i = 0; i < der; ++i)
  		  {
  		  	printf("%d\n",BicisLeft[i] );
  		  }

			if (fork() == 0) {
				for (int i = 0; i <= izq; i++) {		//Proceso hijo se encarga de las bicicletas de la izquierda
					turnoLeft = BicisLeft[i];
					if (turnoLeft > turnoRight) {
						//Up derecha
						//Down izquierda
					} else {
						//Pasa left
					}
				}
			} else {
				for (int j = 0; j <= der; j++) {		//Proceso padre se encarga de las bicicletas de la derecha NOTA: ¿con el else en fork() se evitará que el hijo haga el código?
					turnoRight = BicisRight[j];
					if (turnoRight > turnoLeft) {
						//Up izquierda
						//Down derecha
					} else {
						//Pasa right
					}
				}

			}




  	}
  	fclose(fp);
	return 0;
}


int CuantasB ( FILE *fp,int type){
	const size_t tamlineas = 300; // 0 izq , 1 der
    char *linea= malloc(tamlineas);
    int largo;
    int sentido=0;
    while(fgets(linea,tamlineas,fp)!= NULL){
    	largo=strlen(linea);
    	for (int i = 0; i < largo; i++)
    	{
    		if (type == 0 && linea[i] == 'L') sentido++;
    		if (type == 1 && linea[i] == 'R') sentido++;
   		}

    }
    return sentido;

}

void Bicis(int a[], int type,FILE *fp){
	// type= 0 izq, 1 der
    const size_t tamlineas = 300;
    char *linea= malloc(tamlineas);
    const size_t tamNum=4;
    char *numl=malloc(tamNum);
    int largo;
    int der=0;
    int izq=0;
    int num=0;
    int lastpos=0;
    int j=0;
    while(fgets(linea,tamlineas,fp)!= NULL){
    	largo=strlen(linea);
   		for (int i = 0; i < largo; i++)
    	{
    		if (linea[i] == 'L'){ izq=1;} else{
    		if (linea[i] == 'R'){ der=1;} }
   		}
   		if ((izq == 1 && type == 0) || (der == 1 && type == 1) ){
   			j=0;
   			while (j<largo && linea[j] != ' ') {
   				numl[j]=linea[j];
   				j++;
   			}
   			j=0;
   			a[lastpos]=atoi(numl);
   			//printf("%d\n",a[lastpos]);
   			lastpos++;
   		}
   		izq=0;
   		der=0;

    }
    free(linea);
    free(numl);


}
