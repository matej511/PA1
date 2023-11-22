#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY 2000
#define MAX_SUM_ARRAY 2003000

int input(int arr[] ,int *counter){
    int num;
    int r;
    while ((r=scanf(" %d",&num))!=EOF){
        if((*counter>1999 || r!=1)){
            return 0;
        }
        arr[*counter]=num;
        *counter+=1;
    }
    if (r==EOF && *counter==0){
        return 0;
    }
    return 1;
}

void sumArray(const int arr[], int counter, int arrSum[], int *count){
    long int sum=0;
    for (int i = 0; i < counter -1; i++)
    {
        sum=arr[i];
        for(int j=i+1; j<counter; j++){
            sum+=arr[j];
            arrSum[*count]=sum;
            *count+=1;
        }
        sum=0;
    }
    return;
}

int cmpfunc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int dvojice(const int arrSum[],int counter){
    int count=1;
    int sum=0;
    for (int i = 0; i < (counter-1); i++)
    {
        if(arrSum[i]==arrSum[i+1]){
            count+=1;
        }
        else{
            sum+=(count*(count-1))/2;
            count=1;
        }
    }
    return sum;
}

void print(int count, int arrSum[]){
    printf("%d\n",count);
    for (int i = 0; i < count; i++)
    {
        printf("%d ",arrSum[i]);
    }
    
}

int main(void){
    printf("Posloupnost:\n");
    int arr[MAX_ARRAY];
    int arrSum[MAX_SUM_ARRAY];
    int counter=0;

    if(input(arr,&counter)==0){
        printf("Nespravny vstup.\n");
        return 0;
    }
    int count =0;
    sumArray(arr,counter,arrSum, &count);
    qsort(arrSum,count,sizeof(int),cmpfunc);
    printf("Pocet dvojic: %d\n",dvojice(arrSum,count));
    return 0;
}