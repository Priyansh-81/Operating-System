#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define phil_no 5

sem_t forks[phil_no];

void *philosopher(void* arg){
    int id=*(int*)arg;
    int left=id;
    int right=(id+1)%phil_no;

    while(1){
        printf("Philosopher %d is thinking...\n",id);
        sleep(1);

        if(id%2==0){
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        }else{
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        }

        printf("Philosopher %d is eating...\n",id);
        sleep(2);

        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
    return NULL;
}

int main(){
    pthread_t philosophers[phil_no];
    int ids[phil_no];

    for(int i=0;i<phil_no;i++){
        sem_init(&forks[i],0,1);
    }

    for(int i=0;i<phil_no;i++){
        ids[i]=i;
        pthread_create(&philosophers[i],NULL,philosopher,&ids[i]);
    }
    for(int i=0;i<phil_no;i++){
        pthread_join(philosophers[i],NULL);
    }
    for(int i=0;i<phil_no;i++){
        sem_destroy(&forks[i]);
    }
    return 0;
}
