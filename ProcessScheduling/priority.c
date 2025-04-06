#include<stdio.h>
//assumption smallest number is the highest priority

typedef struct process{
    int pid,priority,bt,wt,tat;
}process;

void sortaccordingtopriority(process processes[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].priority > processes[j+1].priority){
                process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
}

float average_wt(process processes[], int n){
    float sum=0;
    for(int i=0;i<n;i++){
        sum+=processes[i].wt;
    }
    return sum/n;
}

float average_tat(process processes[], int n){
    float sum=0;
    for(int i=0;i<n;i++){
        sum+=processes[i].tat;
    }
    return sum/n;
}


void timecalc(process processes[],int n){
    processes[0].wt=0;

    for(int i=1;i<n;i++){
        processes[i].wt=processes[i-1].wt+processes[i-1].bt;
    }

    for(int i=0; i<n; i++){
        processes[i].tat = processes[i].bt + processes[i].wt;
    }
}

int main(){
    printf("Enter the number of processes: ");
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
    }

    printf("Enter the priority and burst time for the processes\n");
    for(int i=0;i<n;i++){
        printf("Process %d: ",processes[i].pid);
        scanf("%d%d",&processes[i].priority,&processes[i].bt);
    }

    sortaccordingtopriority(processes, n);
    timecalc(processes,n);

    printf("The priority, wait time and turn around time of all the processes is: \n");
    for(int i=0;i<n;i++){
        printf("Process %d:\t%d\t%d\t%d\n",processes[i].pid,processes[i].priority,processes[i].wt,processes[i].tat);
    }
    printf("\nThe average wait time is %.2f and the average turn around time is %.2f\n",average_wt(processes, n),average_tat(processes,n));
    return 0;
}
