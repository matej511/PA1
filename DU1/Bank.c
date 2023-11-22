#include <stdio.h>
#include <stdlib.h>

void cal(double deb, double kred);
double rounded(double credit);

int main(void){
    double kred, deb; //value

    printf("Zadejte kreditni urok [%%]:\n"); //first input
    int r = scanf("%lf",&kred);
    if( r==EOF || r==0|| kred>100 || kred<= 0){
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Zadejte debetni urok [%%]:\n"); //second input
    r = scanf("%lf",&deb);
    if( r==EOF || r==0|| kred>100 || kred<= 0){
        printf("Nespravny vstup.\n");
        return 0;
    }
    cal(deb, kred); //
    return r;
}

void cal(double deb, double kred){
    int day, prevD=-1;
    double money;
    double credit=0;
    printf("Zadejte transakce:\n");
    while (1){
        int r = scanf("%d , %lf", &day, &money);
        // days conditions + input conditions
        if(prevD>=day || r<2 || r==EOF || day<0 ){
            printf("Nespravny vstup.\n");
            return;
        }
        for (int i = 0; i < day-prevD; i++){
            if(credit>=0){
                credit=rounded(credit+(credit*kred*0.01));
            }
            else{
                credit=rounded(credit+(credit*deb*0.01));
            }
        }
        credit+=money;
        if (money==0){  //good end of program
            break;
        }
        prevD=day;
    }
    printf("Zustatek: %.2lf\n",credit);
}

double rounded(double credit){
    int number =credit*100;
    return number*0.01;
}
