//sem_wait resta 1 al semaforo
//sem_post suma 1 al semaforo
//si semaforo vale -1, se queda en wait

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define ESC 3
#define LEC 2

int escritor_c=0,lector_c=0,archivo=5;
sem_t mutex_x,mutex_y,mutex_lector,mutex_escritor;//semáforos
pthread_t w[ESC],r[LEC];//del 0 al índice
char text[100];

/******************************************************************************/

void reader(){
  printf("\n******************************\nLECTOR");

  //lee
  printf("\n%d",archivo);

}//end reader

/******************************************************************************/

void writer(){
  sem_wait(&mutex_escritor);

  printf("\n******************************");
  //inicia escritor
  printf("\nESCRITOR\nEscriba algo:\n");
  //escribe
  fgets(text,sizeof(text),stdin);

  sem_post(&mutex_escritor);
}//end writer

/******************************************************************************/

int main(){
  //Se inicializan los semáforos en 1
  sem_init(&mutex_x,0,1);
  sem_init(&mutex_y,0,1);
  sem_init(&mutex_escritor,0,1);
  sem_init(&mutex_lector,0,1);
  int a,b;

  //CREA

  pthread_create(&r[0],NULL,(void *)reader,NULL);//Lector
  pthread_create(&w[0],NULL,(void *)writer,NULL);
  pthread_create(&w[1],NULL,(void *)writer,NULL);
  pthread_create(&w[2],NULL,(void *)writer,NULL);
  pthread_create(&r[1],NULL,(void *)reader,NULL);//Lector
  pthread_create(&r[2],NULL,(void *)reader,NULL);//Lector
  pthread_create(&w[3],NULL,(void *)writer,NULL);
  pthread_create(&w[4],NULL,(void *)writer,NULL);

  //crea lector
  /*for(a=0;a<=LEC;a++){//LEC=2
    pthread_create(&r[a],NULL,(void *)reader,NULL);
  }

  //crea escritor
  for(b=0;b<=ESC;b++){//ESC=3
    pthread_create(&w[b],NULL,(void *)writer,NULL);
  }*/

  //ESPERA A QUE TERMINE

  //espera lector
  for(a=0;a<=LEC;a++){
    pthread_join(r[a],NULL);
  }

  //espera escritor
  for(b=0;b<=ESC;b++){
    pthread_join(w[b],NULL);
  }

  return(0);
}
