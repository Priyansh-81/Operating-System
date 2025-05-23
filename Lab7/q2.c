#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>

sem_t mutex, writeblock;
int data = 0, rcount = 0;

void *reader(void *arg)
{
  int f = (intptr_t)arg;
  sem_wait(&mutex);
  rcount = rcount + 1;
  if (rcount == 1)
  {
    sem_wait(&writeblock);
  }
  sem_post(&mutex);
  printf("Data read by the reader %d is %d\n", f, data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if (rcount == 0)
  {
    sem_post(&writeblock);
  }
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f = (intptr_t)arg;
  sem_wait(&writeblock);
  data++;
  printf("Data written by the writer %d is %d\n", f, data);
  sleep(1);
  sem_post(&writeblock);
}

int main()
{
  int i;
  pthread_t rtid[5], wtid[5];
  sem_init(&mutex, 0, 1);
  sem_init(&writeblock, 0, 1);
  for (i = 0; i < 3; i++)
  {
    pthread_create(&wtid[i], NULL, &writer, (void *)(intptr_t)i);
    pthread_create(&rtid[i], NULL, &reader, (void *)(intptr_t)i);
  }
  for (i = 0; i < 3; i++)
  {
    pthread_join(wtid[i], NULL);
    pthread_join(rtid[i], NULL);
  }
  return 0;
}

//to execute 
//gcc q2.c -o a2.out -pthread -lrt
//./a2.out
