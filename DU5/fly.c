#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define START_MAX 4

/**
 * @struct FLY
 *comprise data of input
 * pozision of plane and name of plane
*/
typedef struct{
    double x;
    double y;
    char plane[200];
}FLY;

/**
 * @struct DISTANCE
 * comprise data of output
 * minimum distance, name of planes in colision
*/
typedef struct{
    double minimum;
    char plane1[201];
    char plane2[201];
}DISTANCE;

/**
 * read input data form cmp
 * @return array of @struct FLY
 * @return 1 wrong input; 0 good input
*/
int input(FLY **flyed,int *counter){
    int max=START_MAX;
    while (1)
    {
        if(max==*counter){
            max=max*2;
            *flyed=(FLY *)realloc(*flyed,max*sizeof(FLY));
        }
        int r= scanf("%lf , %lf : %199s",&flyed[0][*counter].x,&flyed[0][*counter].y,flyed[0][*counter].plane);
        char c =getchar();
        if(c!= ' ' && c!='\n' && c!=EOF)
            r=0;
        if(r==EOF)
            return 0;
        if(r!=3)
            return 1;
        *counter+=1;
    }

    return 0;
}

/**
 * @return elements to @struct DISTANCE
*/
void addDis(DISTANCE * disc, FLY  name1, FLY name2){
    strcpy(disc->plane1,name1.plane);
    strcpy(disc->plane2,name2.plane);
    double n1 = (pow(name1.x - name2.x,2));
    double n2 = (pow(name1.y - name2.y,2));
    disc->minimum=sqrt(n1+n2);
    return;
}

/**
 * @return added elements to @struct FLY
 * @brief using for predefine minimum distance
*/
void add(FLY number1, FLY number2, FLY * min1, FLY * min2){
    min1->x=number1.x;
    min1->y=number1.y;
    min2->x=number2.x;
    min2->y=number2.y;
}

/**
 * @struct FLY number1 and number2 are one digit
 * @struct FLY number3 and number4 are second digit
 * compare datatype double
 * @return 1 numbers are equal; 0 are not equal
*/
int equale (FLY number1, FLY number2,FLY number3, FLY number4)
{
    double n1 = (pow(number1.x - number2.x,2));
    double n2 = (pow(number1.y - number2.y,2));
    double n3 = (pow(number3.x - number4.x,2));
    double n4 = (pow(number3.y - number4.y,2));
    return (fabs((n1+n2) - (n3+n4)) <= fabs((n1+n2) + (n3+n4))*10000*__DBL_EPSILON__);
}

/**
 * @struct FLY number1 and number2 are one digit
 * @struct FLY min1 and min2 are second digit
 * compare datatype double
 * @return 1 number is smaller than min ; 0 are not smaller
*/
int smaller(FLY number1, FLY number2,FLY min1, FLY min2){
    double n1 = (pow(number1.x - number2.x,2));
    double n2 = (pow(number1.y - number2.y,2));
    double n3 = (pow(min1.x - min2.x,2));
    double n4 = (pow(min1.y - min2.y,2));
    return ((n1+n2) < (n3+n4));
}

/**
 * @brief finding all colision plane
 * @return count of colision plane
 * @return array of @struct DISTANCE
 *  containig name of planes in colision 
*/
int findMin(FLY *flyed,DISTANCE **dist,int counter){
    int max=START_MAX;
    int count=0;
    FLY min1;
    FLY min2;
    add(flyed[1],flyed[0],&min1,&min2);
    for(int i=0; i<counter-1; i++){
        for(int j = i+1; j < counter; j++){
            
            if(max==count){
                max*=2;
                *dist=(DISTANCE*)realloc(*dist,sizeof(DISTANCE)*max);
            }

            if(smaller(flyed[i],flyed[j],min1,min2) && equale(flyed[i],flyed[j],min1,min2) !=1){
                count=0;
                add(flyed[i],flyed[j],&min1,&min2);
            }

            if(equale(flyed[i],flyed[j],min1,min2)){
                addDis(&dist[0][count],flyed[i],flyed[j]);
                count+=1;
            }
        }
        
    }
    return count;
}

/**
 * @brief print all the planes in colision
*/
void print(DISTANCE *flyed,int counter){
    for (int i = 0; i < counter; i++){
        printf("%s - %s\n",flyed[i].plane1,flyed[i].plane2);    
    }
    return;
}

int main(void){
    int counter=0;
    FLY *flyed=(FLY*)malloc(sizeof(FLY)*START_MAX);
    DISTANCE *dist=(DISTANCE *)malloc(sizeof(DISTANCE)*START_MAX);
    printf("Pozice letadel:\n");
    if(input(&flyed,&counter)==1 || counter<2){
        printf("Nespravny vstup.\n");
        free(flyed);
        free(dist);
        return 0;
    }
    int count = findMin(flyed,&dist,counter);
    printf("Vzdalenost nejblizsich letadel: %lf\n",dist[0].minimum);
    printf("Nalezenych dvojic: %d\n",count);
    print(dist,count);
    free(flyed);
    free(dist);
    return 0;
}