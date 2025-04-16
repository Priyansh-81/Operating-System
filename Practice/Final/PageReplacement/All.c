#include<stdio.h>
#include<stdlib.h>

int inFrame(int frames[], int f, int page){
    for(int i=0;i<f;i++){
        if(frames[i]==page){
            return 1;
        }
    }
    return 0;
}

void fifo(int page[], int n, int f){
    int frames[f];
    int front=0, pagefaults=0;

    for(int i=0;i<f;i++){
        frames[i]=-1;
    }

    printf("\nPage\tFrames\n");

    for(int i=0;i<n;i++){
        if(!inFrame(frames,f,page[i])){
            frames[front]=page[i];
            front=(front+1)%f;
            pagefaults++;
            printf("%d\t",page[i]);
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    printf("-");
                }else{
                    printf("%d", frames[j]);
                }
            }
            printf("\n");
        }else{
            printf("HIT\n");
        }
    }
    printf("Total number of page faults: %d\n",pagefaults);
}

int main(){
    int n;
    printf("Enter the number of pages: ");
    scanf("%d",&n);
    int f;
    printf("Enter the number of frames: ");
    scanf("%d",&f);
    int page[n];
    printf("Enter the page sequence:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&page[i]);
    }
    fifo(page,n,f);
    return 0;
}
