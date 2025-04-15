#include<stdio.h>
#include<stdlib.h>

void sort(int req[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(req[j]>req[j+1]){
                int temp=req[j+1];
                req[j+1]=req[j];
                req[j]=temp;
            }
        }
    }
}

int fcfs(int requests[],int n, int head){
    int seektime=0;
    for(int i=0;i<n;i++){
        seektime+=abs(requests[i]-head);
        head=requests[i];
    }
    return seektime;
}

int sstf(int requests[], int n, int head){
    int count=0,seektime=0;
    int visited[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    int min, minIndex;
    while(count<n){
        min=99999;
        for(int i=0;i<n;i++){
            if(!visited[i] && abs(head-requests[i])<min){
                min=abs(head-requests[i]);
                minIndex=i;
            }
        }
        seektime+=abs(head-requests[minIndex]);
        head=requests[minIndex];
        visited[minIndex]=1;
        count++;
    }
    return seektime;
}

int scan(int requests[], int n, int head,  int direction, int disk_size){
    int seektime=0;
    int pos;
    sort(requests,n);
    for(pos=0;pos<n;pos++){
        if(requests[pos]>head){
            break;
        }
    }
    if(direction==1){
        for(int i=pos;i<n;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        if(head!=disk_size-1){
            seektime+=abs(head-disk_size+1);
            head=disk_size-1;
        }
        for(int i=pos-1;i>=0;i--){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }else{
        for(int i=pos-1;i>=0;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        if(head!=0){
            seektime+=abs(head);
            head=0;
        }
        for(int i=pos;i<n;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }
    return seektime;
}

int cscan(int requests[], int n, int head, int disk_size){
    int seektime=0;
    int pos;
    sort(requests,n);
    for(pos=0;pos<n;pos++){
        if(requests[pos]>head){
            break;
        }
    }
    for(int i=pos;i<n;i++){
        seektime+=abs(head-requests[i]);
        head=requests[i];
    }
    if(head!=disk_size-1){
        seektime+=abs(head-(disk_size-1));
        head=disk_size-1;
    }
    seektime+=abs(head);
    head=0;
    for(int i=0;i<pos;i++){
        seektime+=abs(head-requests[i]);
        head=requests[i];
    }
    return seektime;
}
int look(int requests[], int n, int head, int direction){
    int seektime=0;
    int pos;
    sort(requests,n);
    for(pos=0;pos<n;pos++){
        if(requests[pos]>head){
            break;
        }
    }
    if(direction==1){
        for(int i=pos;i<n;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        for(int i=pos-1;i>=0;i--){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }else{
        for(int i=pos-1;i>=0;i--){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        for(int i=pos;i<n;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }
    return seektime;
}
int clook(int requests[], int n, int head, int direction){
    int seektime=0;
    int pos;
    sort(requests, n);
    for(pos=0;pos<n;pos++){
        if(requests[pos]>head){
            break;
        }
    }
    if(direction==1){
        for(int i=pos;i<n;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        if(pos>0){
            seektime+=abs(head-requests[0]);
            head=requests[0];
        }
        for(int i=0;i<pos;i++){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }else{
        for(int i=pos-1;i>=0;i--){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
        if(pos<n){
            seektime+=abs(head-requests[n-1]);
            head=requests[n-1];
        }
        for(int i=n-1;i>=pos;i--){
            seektime+=abs(head-requests[i]);
            head=requests[i];
        }
    }
    return seektime;
}

int main(){
    printf("Enter the number of requests to be served: ");
    int n;
    scanf("%d",&n);
    int requests[n];
    printf("Enter the requests:\n");
    for(int i=0;i<n;i++){
        printf("Enter request %d: ",i+1);
        scanf("%d",&requests[i]);
    }
    int head;
    printf("Enter the positions of head: ");
    scanf("%d",&head);
    int disk_size;
    printf("Enter the number of cylinders in the disk: ");
    scanf("%d",&disk_size);
    int direction;
    printf("Enter the direction in which the algo should start from\n1 for right\n-1 for left\n");
    scanf("%d",&direction);
    printf("\nFCFS: %d\nSSTF: %d\nSCAN: %d\nCSCAN: %d\nLOOK: %d\nCLOOK: %d\n",fcfs(requests,n,head),sstf(requests,n,head),scan(requests,n,head, direction,disk_size),cscan(requests, n, head, disk_size),look(requests,n,head,direction),clook(requests,n,head, direction));
    return 0;
}
