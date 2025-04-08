#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCE 10

int buffer[BUFFER_SIZE];
int in=0,out=0;

sem_t empty;
sem_t full;
sem_t s;

void *producer(void *args){
    for(int i=0;i<NUM_PRODUCE;i++){
        int item=i+1;//producing item

        sem_wait(&empty);
        sem_wait(&s);//acquire lock

        buffer[in]=item;
        printf("Producer produced %d\n",item);
        in=(in+1)%BUFFER_SIZE;

        sem_post(&s);//release lock after crit exec
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *args){
    for(int i=0;i<NUM_PRODUCE;i++){
        sem_wait(&full);
        sem_wait(&s);//acquire

        int item=buffer[out];
        printf("Consumer consumed %d\n",item);
        out=(out+1)%BUFFER_SIZE;

        sem_post(&s);//release
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main(){
    pthread_t prodThread,conThread;

    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    sem_init(&s,0,1);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&conThread, NULL,consumer,NULL);

    pthread_join(prodThread,NULL);
    pthread_join(conThread,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&s);
    return 0;
}
