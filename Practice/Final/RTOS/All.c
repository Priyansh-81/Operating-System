#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id;
    int etime;
    int period;
    int deadline;
    int next;
    int remtime;
}task;

int gcd(int a, int b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}

int lcm(int a, int b){
    return ((a*b)/gcd(a,b));
}

int hyperperiod(task tasks[], int n){
    int simtime=tasks[0].period;
    for(int i=1;i<n;i++){
        simtime=lcm(simtime,tasks[i].period);
    }
    return simtime;
}

void sort_period(task tasks[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(tasks[j+1].period<tasks[j].period){
                task temp=tasks[j+1];
                tasks[j+1]=tasks[j];
                tasks[j]=temp;
            }
        }
    }
}

void sort_deadline(task tasks[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(tasks[j+1].deadline<tasks[j].deadline){
                task temp=tasks[j+1];
                tasks[j+1]=tasks[j];
                tasks[j]=temp;
            }
        }
    }
}

void rms(task tasks[], int n, int simtime){
    sort_period(tasks, n);
    for(int t=0;t<simtime;t++){
        for(int i=0;i<n;i++){
            if(t==tasks[i].next){
                tasks[i].remtime=tasks[i].etime;
                tasks[i].next+=tasks[i].period;
            }
        }
        int scheduled=0;
        for(int i=0;i<n;i++){
            if(tasks[i].remtime>0){
                printf("Time %d: %d\n",t,tasks[i].id);
                tasks[i].remtime--;
                scheduled=1;
                break;
            }
        }
        if(!scheduled){
            printf("Time %d: IDLE\n",t);
        }
    }
}

void edf(task tasks[], int n, int simtime){
    for(int t=0;t<simtime;t++){
        for(int i=0;i<n;i++){
            if(t==tasks[i].next){
                tasks[i].remtime=tasks[i].etime;
                tasks[i].deadline=t+tasks[i].period;
                tasks[i].next+=tasks[i].period;
            }
        }

        sort_deadline(tasks,n);
        int scheduled=0;
        for(int i=0;i<n;i++){
            if(tasks[i].remtime>0){
                printf("Time %d: %d\n",t,tasks[i].id);
                tasks[i].remtime--;
                scheduled=1;
                break;
            }
        }
        if(!scheduled){
            printf("Time %d: IDLE\n",t);
        }

    }
}

int main(){
    int n;
    printf("Enter the number of tasks: ");
    scanf("%d",&n);
    task tasks[n];
    for(int i=0;i<n;i++){
        tasks[i].id=i+1;
        tasks[i].remtime=0;
        tasks[i].next=0;
    }
    printf("Enter the period and Execution time for the tasks\n");
    for(int i=0;i<n;i++){
        printf("Task %d: ",tasks[i].id);
        scanf("%d%d",&tasks[i].period,&tasks[i].etime);
        tasks[i].deadline=tasks[i].period;
    }
    int simtime=hyperperiod(tasks,n);
    rms(tasks,n,simtime);
    printf("\n");
    edf(tasks,n,simtime);
    return 0;
}
