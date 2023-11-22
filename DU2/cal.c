#include <stdio.h>

int prime(int num);
int proper(int num); 
int cal(char c, int start, int end);

int main(void){
    printf("Intervaly:\n");
    int start, end;
    char c;

    while (1)
    {
        int r = scanf(" %c %d %d",&c,&start,&end);
        
        if(r==EOF){
            break;
        }
        if((start<1 || start>end  || r!=3) || (c!='#' && c!='?')){
            printf("Nespravny vstup.\n");
            return 0;
        }

        printf("Celkem: %d\n",cal(c,start,end));
    }
    
}

int proper(int num){
    int result = 0;
    if(num == 1){
        return result;
    }
    for(int i = 2; i*i <= num;i++){
        if(num % i == 0){
            if(i == (num / i)){
                result += i;
            }
            else{
                result += (i + num/i);
            }
        }
    }
    return (result + 1);
}

int prime(int num){
    if(num<2){
        return 0;
    }
    if(num==2){
        return 0;
    }
    if(num%2==0){
        return 0;
    }
    for (int i = 3; i*i <= num; i+=2)
    {
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

int cal(char c, int start, int end){
    int counter=0;
    for(int i=start; i<=end;i++){
        if(prime(proper(i))==1 && i!=1){
            if(c=='?')
                printf("%d\n", i);
            counter+=1;
        }
    }
    return counter;
}