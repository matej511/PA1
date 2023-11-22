#include <stdlib.h>
#include <stdio.h>



/*LINKED LIST*/
typedef struct Node
{
    int data;
    struct Node *next;
}Node_t;

/*LINKED LIST FUNCTION*/
void append(Node_t** tokens, int data)  //Add data on the last 
{
    Node_t* newNode=(Node_t*)malloc(sizeof(Node_t));
    newNode->data=data;
    newNode->next=NULL;
    if(*tokens==NULL)
    {
        *tokens=newNode;
        return;
    }    
    Node_t *temp=*tokens;
    while (temp->next !=NULL)
        temp=temp->next;
    temp->next=newNode;
    return;
}
int pop(Node_t** token, int *data)  //Take off the data from first
{
    if(*token==NULL)
        return 0;
    Node_t* temp=*token;
    *data=(*token)->data;
    (*token)=(*token)->next;
    free(temp);
    return 1;
}
void push(Node_t** token,int data)  //Add data on the first
{
    Node_t* temp=(Node_t*)malloc(sizeof(Node_t));
    temp->next=*token;
    temp->data=data;
    *token=temp;

}
void clear(Node_t* token)   //Clear memory from LL
{
    if(token==NULL)
        return;
    while (token!=NULL)
    {
        Node_t* tmp=token->next;
        free(token);
        token=tmp;
    }
    return;
}
void clearAll(Node_t* north, Node_t* south, Node_t* west, Node_t* east)
{
    clear(north);
    clear(south);
    clear(east);
    clear(west);
}

int numberElements(Node_t * node)
{
    Node_t* token=node;
    int counter=0;
    while (token!=NULL)
    {
        counter++;
        token=token->next;
    }
    return counter;
}
int maxLevel(Node_t* north, Node_t* south, Node_t* east, Node_t* west)
{
    int level=0;
    level+=numberElements(north);
    level+=numberElements(east);
    level+=numberElements(south);
    level+=numberElements(west);
    return level;
}

/*Function used in poping*/
int recursion(Node_t** north,Node_t** south,Node_t** west,Node_t** east, int level, int score, int maxLevel, char* moves);
/*PREPARE FOR GAME*/
int control(char *read, char c)
{
    int i=0;
    if(c!='S' && c!='W' && c!='E' && c!='N')
        return 1;
    while (read[i]!='\0')
    {
        if(read[i]==c)
            return 1;
        i++;
    }
    read[i]=c;
    read[i+1]='\0';
    return 0;
}
int input(Node_t** north,Node_t** south,Node_t** west,Node_t** east, char *used, int *total, int *maxLevel)    //Read inputs and check if all is right
{
    char s1;
    char s2;
    int r=scanf(" %c: %c", &s1, &s2);
    if (control(used,s1))
        return 0;
    if(s1!= 'N' && s1!= 'W' && s1!= 'E' && s1!= 'S' && s2!='{' && r!=2)
        return 0;
    int number;
    int counter=0;
    while ((r=scanf(" %d",&number))!=EOF)
    {   
        if(counter>31 || r==0)
            return 0;
        if(s1=='N')
            append(north,number);
        if(s1=='S')
            append(south,number);
        if(s1=='W')
            append(west,number);
        if(s1=='E')
            append(east,number);
        *total+=number;
        char c;
        c='\0';        
        while(scanf(" %c",&c)!=EOF)
        {
             if(c!=',' && c!= '}')
            {
                return 0;
            }
            if(c=='}' || c==',' )
                break;
        }
        if(c=='}')
            break;
        counter++;
    }
    *maxLevel+=counter+1;
    return 1;
}
void readInput(Node_t** north,Node_t** south,Node_t** west,Node_t** east, int* total, int *maxLevel, char* read)
{
    if(input(north,south, west, east,read,total,maxLevel)==0)
    {
        printf("Nespravny vstup.\n");
        clearAll( *north, *south, *west, *east);
        exit(0);
    }
}

/*PLAY*/
void print(Node_t *token)
{
    while (token!=NULL)
    {
        printf("%d ",token->data);
        token=token->next;
    }
    printf("\n");
}

int min(int m1, int m2, int m3, int m4)
{
    if(m1==-1*__INT_MAX__)
        m1*=-1;
    if(m2==-1*__INT_MAX__)
        m2*=-1;
    if(m3==-1*__INT_MAX__)
        m3*=-1;
    if(m4==-1*__INT_MAX__)
        m4*=-1;
    int minimal=m1;
    if(minimal>m2)
        minimal=m2;
    if(minimal>m3)
        minimal=m3;
    if(minimal>m4)
        minimal=m4;
    return minimal;
}

int max(int m1, int m2, int m3, int m4)
{
    int maximal=m1;
    if(maximal<m2)
        maximal=m2;
    if(maximal<m3)
        maximal=m3;
    if(maximal<m4)
        maximal=m4;
    return maximal;
}

int poping(Node_t** token, Node_t** north,Node_t** south,Node_t** west,Node_t** east, int level, int score, int maxLevel, char* moves)
{
    int m=-1*__INT_MAX__;;
    int number;
    if(pop(token,&number))
    {
        int prev=score;
        if(level%2!=0)
            score+=number;
        m=recursion(north,south,west,east,level, score,maxLevel,moves);
        score=prev;
        push(token,number);
    }
    return m;
}
int recursion(Node_t** north,Node_t** south,Node_t** west,Node_t** east, int level, int score, int maxLevel, char* moves)
{
    int m1=-1*__INT_MAX__, m2=-1*__INT_MAX__, m3=-1*__INT_MAX__, m4=-1*__INT_MAX__;
    if(north!=NULL && south !=NULL && east!=NULL && west!=NULL && level<13)
    {
        m1=poping(north,north,south,west,east,level+1,score,maxLevel,moves);
        m2=poping(south,north,south,west,east,level+1,score,maxLevel,moves);
        m3=poping(west,north,south,west,east,level+1,score,maxLevel,moves);
        m4=poping(east,north,south,west,east,level+1,score,maxLevel,moves);
    }
    if(level==0)
    {
        if(m1==max(m1,m2,m3,m4))
            *moves='N';
        else if(m2==max(m1,m2,m3,m4))
            *moves='S';
        else if(m3==max(m1,m2,m3,m4))
            *moves='W';
        else if(m4==max(m1,m2,m3,m4))
            *moves='E';
    }
   // printf("%d %d %d %d\n", m1,m2,m3,m4);
    if(level==maxLevel || level==13)
        return score;
    if(level%2==0)
    {
       // printf("Max: %d lvl%d\n",max(m1,m2,m3,m4),level);
        return max(m1,m2,m3,m4);
    }
    else
    {
        //printf("Min: %d lvl %d\n",min(m1,m2,m3,m4),level);
        return min(m1,m2,m3,m4);
    }
}

void play(Node_t** north,Node_t** south,Node_t** west,Node_t** east,int maxLevel)
{
    int socre1=0, score2=0, nor=0,sou=0,wes=0,eas=0;
    for(int i=0; i<maxLevel; i++)
    {
        char moves='\0';
        int number=0,pozition=0;
        if(i%2==0)
            recursion(north,south, west, east,0,socre1,maxLevel-i, &moves);
        else
            recursion(north,south, west, east,0,score2,maxLevel-i, &moves);
        
        if(moves=='N')
        {
            pop(north,&number);
            pozition=nor;
            nor++;
        }
        else if(moves=='S')
        {
            pop(south,&number);
            pozition=sou;
            sou++;
        }
        else if(moves=='W')
        {
            pop(west,&number);
            pozition=wes;
            wes++;
        }
        else if(moves=='E')
        {
            pop(east,&number);
            pozition=eas;
            eas++;
        }
        if(i%2==0)
        {
            socre1+=number;
            printf("A: %c[%d] (%d)\n",moves,pozition,number);
        }
        else
        {
            score2+=number;
            printf("B: %c[%d] (%d)\n",moves,pozition,number);
        }
    }
    printf("Celkem A/B: %d/%d\n",socre1, score2 );
}

int main()
{
    Node_t* north=NULL, * south=NULL, * west=NULL, * east=NULL;
    int total=0, maxLevel=0;
    printf("Zetony:\n");
    
    //input
    char read[5]; read[0]='\0';
    readInput(&north,&south, &west, &east, &total, &maxLevel,read);
    readInput(&north,&south, &west, &east, &total, &maxLevel,read);
    readInput(&north,&south, &west, &east, &total, &maxLevel,read);
    readInput(&north,&south, &west, &east, &total, &maxLevel,read);
    //char moves;
    //int player=recursion(&north,&south, &west, &east,0,0,maxLevel, &moves);
    
    play(&north,&south,&west,&east,maxLevel);
    clearAll( north, south, west, east);
    return 0;
}
