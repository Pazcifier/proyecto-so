#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

void Bicis(int a[], int type, FILE *fp);
int CuantasB(FILE *fp,int type);
void Paso(sem_t mutex, sem_t semDown, sem_t semUp, int DaPaso, int CedePaso);

int main(int argc, char const *argv[]){
	//sem_t *semI =sem_open("Izq",O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	//sem_t *semD =sem_open("Der",O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,1);
	sem_t semD, semI, mutex;
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

			turnoLeft = BicisLeft[0];
			turnoRight = BicisRight[0];
			bool turno;

			if (turnoLeft > turnoRight) {
				sem_init(&semI, 1, -1);
				sem_init(&semD, 1, 0);
				turno = false;
			}	else {
				sem_init(&semI, 1, 0);
				sem_init(&semD, 1, -1);
				turno = true;
			}
			sem_init(&mutex, 1, 1);

				//Con un while acá podría funcionar pero explota
				for (int i = 0; i < 2; i++) {
					if (fork() == 0) {
						break;
					} else {
						//printf("Soy un proceso\n");
						if (turno) {
							sem_wait(&mutex);
							for (int j = 0; j <= izq; j++) {
								turnoLeft = BicisLeft[j];
								printf("TurnoLeft: %d\n", turnoLeft);
								if (turnoLeft > turnoRight) {
									turno = false;
									EspejoJ = j;
									//sem_wait(&semI);
									//sem_post(&semD);
									break;
								} else {
									//Pasa left
									printf("Paso el %d del carril izquierdo\n", turnoLeft);
								}
							}
							sem_post(&mutex);
						} else {
						sem_wait(&mutex);
						for (int k = 0; k <= der; k++) {
							turnoRight = BicisRight[k];
							printf("TurnoRight: %d\n", turnoRight);
							if (turnoRight > turnoLeft) {
								turno = true;
								EspejoK = k;
								//sem_wait(&semD);
								//sem_post(&semI);
								break;
							} else {
								//Pasa right
								printf("Paso el %d del carril derecho\n", turnoRight);
							}
						}
						sem_post(&mutex);
					}
				}
			}
  	fclose(fp);
	return 0;
}
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

void Paso(sem_t mutex, sem_t semDown, sem_t semUp, int DaPaso, int CedePaso) {
	if (DaPaso > CedePaso) {
		sem_wait(&semDown);
		sem_post(&semUp);
	} else {
		sem_wait(&mutex);
		printf("Estoy dando paso\n");
		sem_post(&mutex);
	}
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
