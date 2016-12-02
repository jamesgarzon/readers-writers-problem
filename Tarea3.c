//sem_wait resta 1 al semaforo
//sem_post suma 1 al semaforo
//si semaforo vale -1, se queda en wait

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

char texto[100];
int contador=0;
FILE *archivo;

//threads
pthread_t w[50],r[50];

//Semáforos
sem_t mutex;
sem_t lector;

/******************************************************************************/

void read(){
  sem_wait(&lector);
  //ZONA CRITICA
  archivo = fopen("entrada.txt", "r");
  printf("\n******************************\nLECTOR");
  printf("\nleyendo...");
  fclose(archivo);
  //FINAL ZONA CRITICA
  sem_post(&lector);
}//end read

/******************************************************************************/

void write(){
  sem_wait(&mutex);
  contador++;
  if(contador==1){
    sem_wait(&lector);
  }
  //ZONA CRITICA
  printf("\n*****************************\nESCRITOR");
  archivo=fopen("entrada.txt","a");
  printf("\nEscriba algo:");
  fgets(texto,sizeof(texto),stdin);
  fputs(texto,archivo);
  fclose(archivo);
  //FINAL ZONA CRITICA
  sem_post(&mutex);

  sem_wait(&mutex);
  contador--;
  if(contador==0){
    sem_post(&lector);
  }
  sem_post(&mutex);
}//end write

/******************************************************************************/

int proceso(int ESC,int LEC){
  //Se inicializan los semáforos en 1
  sem_init(&mutex,0,1);
  sem_init(&lector,0,1);
  int a,b;

  //Primero se crea 1 único escritor
  pthread_create(&w[0],NULL,(void *)write,NULL);

  //Luego se crean los lectores
  for(a=0;a<=LEC;a++){
    pthread_create(&r[a],NULL,(void *)read,NULL);
  }

  //Finalmente el resto de los escritores
  for(b=1;b<=ESC;b++){
    pthread_create(&w[b],NULL,(void *)write,NULL);
  }

  //Espera lectores
  for(a=0;a<=LEC;a++){
    pthread_join(r[a],NULL);
  }

  //Espera escritores
  for(b=0;b<=ESC;b++){
    pthread_join(w[b],NULL);
  }

  printf("\n");
  return 0;
}

/******************************************************************************/

int main(){
  char caja[100];
  int writer,reader;

  //LECTOR
  printf("Ingrese la cantidad de lectores:\n");
  fgets(caja,sizeof(texto),stdin);
  sscanf(caja,"%d",&reader);

  while(reader==0 || reader>20){
    printf("Ingrese un numero valido menor a 20\n");
    fgets(caja,sizeof(texto),stdin);
    sscanf(caja,"%d",&reader);
  }
  //END LECTOR

  //ESCRITOR
  printf("Ingrese la cantidad de escritores:\n");
  fgets(caja,sizeof(texto),stdin);
  sscanf(caja,"%d",&writer);

  while(writer==0 || writer>20){
    printf("Ingrese un numero valido menor a 20\n");
    fgets(caja,sizeof(texto),stdin);
    sscanf(caja,"%d",&writer);
  }
  //END ESCRITOR

  proceso(writer-1,reader-1);

  return(0);
}
