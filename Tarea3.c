//sem_wait resta 1 al semaforo
//sem_post suma 1 al semaforo
//si semaforo vale -1, se queda en wait

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define ESC 3
#define LEC 2

char text[100];
int contador=0;

//threads
pthread_t w[ESC],r[LEC];

//Semáforos
sem_t mutex;
sem_t lector;

/******************************************************************************/

void read(){
  sem_wait(&lector);

  printf("\n******************************\nLECTOR");
  printf("\nleyendo...");

  sem_post(&lector);
}//end read

/******************************************************************************/

void write(){
  sem_wait(&mutex);
  contador++;
  if(contador==1){
    sem_wait(&lector);
  }
  printf("\n*****************************\nESCRITOR");
  printf("\nEscriba algo:");
  fgets(text,sizeof(text),stdin);
  printf("\nprint: %s",text);
  sem_post(&mutex);

  sem_wait(&mutex);
  contador--;
  if(contador==0){
    sem_post(&lector);
  }
  sem_post(&mutex);
}//end write

/******************************************************************************/

int main(){
  //Se inicializan los semáforos en 1
  sem_init(&mutex,0,1);
  sem_init(&lector,0,1);
  int a,b;

  //CREA

  pthread_create(&r[0],NULL,(void *)read,NULL);//Lector
  pthread_create(&w[0],NULL,(void *)write,NULL);
  pthread_create(&w[1],NULL,(void *)write,NULL);
  pthread_create(&w[2],NULL,(void *)write,NULL);
  pthread_create(&r[1],NULL,(void *)read,NULL);//Lector
  pthread_create(&r[2],NULL,(void *)read,NULL);//Lector
  pthread_create(&w[3],NULL,(void *)write,NULL);
  pthread_create(&w[4],NULL,(void *)write,NULL);

  //crea lector
  /*for(a=0;a<=LEC;a++){//LEC=2
    pthread_create(&r[a],NULL,(void *)read,NULL);
  }

  //crea escritor
  for(b=0;b<=ESC;b++){//ESC=3
    pthread_create(&w[b],NULL,(void *)write,NULL);
  }*/

  //ESPERA A QUE TERMINE

  //espera lector
  for(a=0;a<=LEC+1;a++){
    pthread_join(r[a],NULL);
  }

  //espera escritor
  for(b=0;b<=ESC+1;b++){
    pthread_join(w[b],NULL);
  }

  return(0);
}
