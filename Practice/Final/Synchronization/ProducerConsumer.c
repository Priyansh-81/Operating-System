#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define size 5

int buffer[size];
int in=0, out=0;

sem_t full;
sem_t empty;
sem_t mutex;

void* producer(void* arg){
    int item;
    for(int i=0;i<10;i++){
        item=rand()%100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in]=item;
        printf("Produced item %d at index %d\n",item, in);
        in=(in+1)%size;

        sem_post(&mutex);
        sem_post(&full);

        sleep(2);
    }
    return NULL;
}

void* consumer(void* arg){
    int item;
    for(int i=0;i<10;i++){
        sem_wait(&full);
        sem_wait(&mutex);

        item=buffer[out];
        printf("Consumed item %d at index %d\n",item,out);
        out=(out+1)%size;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main(){
    pthread_t prod,cons;

    sem_init(&full,0,0);
    sem_init(&empty,0,size);
    sem_init(&mutex,0,1);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);
    return 0;
}
