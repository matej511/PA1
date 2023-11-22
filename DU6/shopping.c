#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/********LowerCase********************************************************/
char *lowerString(char *buffer)
{
    for(long int i=0; i<(long int)strlen(buffer); i++)
    {
        buffer[i]=tolower(buffer[i]);
    }
    return buffer;
}



/***********************LINKEDLIST*****************************************/
/*Linked list for products*/
typedef struct Products
{
    char protuct[201];
    char lowerProduct[201];
    int data;
    char regalProduct[201];
    struct Products* next;
}Products_t;
/**Add product to LinkedList*/
void newProduct(Products_t** products,char *product, const char *regalProd)
{
    Products_t* temp=(Products_t*)malloc(sizeof(Products_t));
    Products_t* last=*products;
    strcpy(temp->protuct,product);
    strcpy(temp->regalProduct,regalProd);
    strcpy(temp->lowerProduct,lowerString(product));
    temp->next=NULL;
    if(*products==NULL)
    {
        *products=temp;
        return;
    }
    while (last->next!=NULL)
    {
        last=last->next;
    }
    last->next=temp;
    return;
}
/**Clear LINKED LIST*/
void clearLinkedList(Products_t* products)
{
    while (products!=NULL)
    {
        Products_t *temp=products->next;
        free(products);
        products=temp;
    }
    
}



/*************QUOTE FROM LINKED LIST***************************************/
/*linked list for quote*/
typedef struct Node
{
    int regals;
    Products_t* products;
    struct Node* next;
}Node_t;
/*quote*/
typedef struct Quote
{
    Node_t *first;
    Node_t *last;
}Quote_t;
/**Node of linked list*/
Node_t* newNode(int regal)
{
    Node_t* node=(Node_t *)malloc(sizeof(Node_t));
    node->regals=regal;
    node->products=NULL;
    node->next=NULL;
    return node;
}

/**Creat Quote*/
Quote_t* creatQuote()
{
    Quote_t* quote=(Quote_t*)malloc(sizeof(Quote_t));
    quote->first=NULL;
    quote->last=NULL;
    return quote;
}

/**Create new node of quote */
void add(Quote_t* quote, int regal)
{
    Node_t* node = newNode(regal);
    if(!quote->last)
    {
        quote->first = quote->last= node;
        return;
    }

    quote->last->next=node;
    quote->last=node;
    return;
}

void addSort(Quote_t* quote, int regal, char* product,char *name)
{
    Node_t* node=newNode(regal);
    //prazdna fronta
    if(!quote->last)
    {
        quote->first=quote->last=node;
        newProduct(&quote->first->products,product,name);
        return;
    }
    //pokud uz regal na zacatku existuje tak nic neprobehne
    if(quote->first->regals==regal)
    {    
        newProduct(&quote->first->products,product,name);
        free(node);
        return;
    }
    //pridani na zacatek
    if(quote->first->regals > regal)
    {
        node->next=quote->first;
        quote->first=node;
        newProduct(&quote->first->products,product,name);
        return;
    }

    //sort
    Quote_t temp=*quote;
    while (temp.first->next!=NULL && temp.first->next->regals<regal)
    {
        temp.first=temp.first->next;
    }    
    if(temp.first->next!=NULL)
    {
        //pokud je u prostred vynech
        if (temp.first->next->regals==regal)
        {
            newProduct(&temp.first->next->products,product,name);
            free(node);
            return;
        }
        node->next=temp.first->next;
    }
    temp.first->next=node;
    newProduct(&temp.first->next->products,product,name);
    return;
}

/**free memory from quote*/
void clearQuote(Quote_t * quote)
{
    if(quote->first==NULL)
    {
        free(quote);
        return;
    }
    while (quote->first!=NULL)
    {
        Node_t* temp = quote->first->next;
        clearLinkedList(quote->first->products);
        free(quote->first);
        quote->first=temp;
    }
    free(quote);
}



/******Print to file****************************************************/
void printfLinkedList(Products_t* products, int regal,int* position)
{
    while (products!=NULL)
    {
        if(regal!=-1)
            printf(" %d. %s -> #%d %s\n",*position,products->protuct,regal,products->regalProduct);
        else
            printf(" %d. %s -> %s\n",*position,products->protuct,products->regalProduct);
        Products_t *temp=products->next;
        free(products);
        *position+=1;
        products=temp;
    }
    
}
void printfQuote(Quote_t * quote, Products_t* noList)
{
    int position =0;
    while (quote->first!=NULL)
    {
        Node_t* temp = quote->first->next;
        printfLinkedList(quote->first->products,quote->first->regals,&position) ;
        free(quote->first);
        quote->first=temp;
    }
    free(quote);
    printfLinkedList(noList,-1,&position);
}


/**************searching but not ideal worst idea*********************/
int searchLinkedList(Products_t products,const char *name,char *buffer)
{
    Products_t *temp=&products;
    int maxLen=0;
    while (temp!=NULL)
    {   char *string=strstr(temp->lowerProduct,name);
        if(string!=NULL)
        {
            int len=strspn(name,temp->lowerProduct);
            //printf("%d %s #%s\n",len,temp->lowerProduct,name);
            if(len>maxLen)
            {
                strcpy(buffer,temp->protuct);
                maxLen=len;
            }
        }
        temp=temp->next;
    }
    return maxLen;
}
int searchQuote(Quote_t* list, Quote_t quote, char *name)
{
    char temp[201];
    int regal=0;
    char help[201]; strcpy(help,name);  //change letters to lower
    int lenName=(int)strlen(name); // len of name of product
    int maxLen=0;
    lowerString(help);
    while (quote.first!=NULL)
    {
        char buffer[201];
        buffer[0]='\0';
        if(quote.first->products==NULL)
        {
            quote.first=quote.first->next;
            continue;
        }
        int len=searchLinkedList(*quote.first->products, help,buffer);
        if(len!=0)
        {   
            if(len>maxLen)
            {
                //printf("[<]%d %s #%s\n",len,buffer,name);
                maxLen=len;
                strcpy(temp,buffer);
                regal=quote.first->regals;
                quote.first=quote.first->next;
                continue;
            }
            if (len==maxLen)
            {
                int lenBuffer=(int)strlen(buffer);
                if(lenName==lenBuffer)
                {
                   //printf("[==]%d %s #%s\n",len,buffer,name);
                    strcpy(temp,buffer);
                    regal=quote.first->regals;
                    break;
                }
                if(regal>quote.first->regals)
                {
                    strcpy(temp,buffer);
                    regal=quote.first->regals;
                }
                    //printf("[==]%d %s #%s\n",len,buffer,name);
            }
            
        }
        quote.first=quote.first->next;
    }
    if(maxLen!=0)
    {
        addSort(list,regal,name,temp);
        return 1;
    }
    return -1;
       
}



/**********REGALS*********************************/
/**Get products in regal*/
int readRegals(Quote_t** quote){
    char buffer[201];
    int past=-1;
    char enter[2]; enter[0]='\n';enter[1]='\0';

    while (fgets(buffer,200,stdin))
    {
        if(past==-1 && buffer[0]!='#')
            return 1;
        if(buffer[0]=='\n')
            break;
        //osetrit;
        if(buffer[0]=='#')
        {
            char buff[20];
            strcpy(buff,buffer+1);
            past+=1;
            if(past != atoi(buff))    //wrong input
                return 1;
            add(*quote,atoi(buff));
            continue;
        }
        int p = strcspn(buffer,enter);
        if(p!=0)
            buffer[p]='\0';
        newProduct(&(*quote)->last->products,buffer,buffer);
    }    
    return 0;
}

/**ragals compare with list*/
int commodity(Quote_t* quote, int null)
{
    char buffer[201];
    Quote_t* list=creatQuote();
    Products_t *notList=NULL;
    while(fgets(buffer,200,stdin))
    {
        null=1;
        char enter[2]; enter[0]='\n';enter[1]='\0';
        int p = strcspn(buffer,enter);
        if(p!=0)
            buffer[p]='\0';

        if(buffer[0]=='\n')
        {
            printf("Optimalizovany seznam:\n");
            printfQuote(list,notList);
            commodity(quote, null);
            return 0;
        } 

        //pozistion in regal and product in regal;
        int s=searchQuote(list, *quote,buffer);
        if(s==-1)
        {
            newProduct(&notList,buffer,"N/A");
        }
    }
    if(null == 0)
    {
        clearQuote(list);
        return 1;
    }
    printf("Optimalizovany seznam:\n");
    printfQuote(list,notList);
    return 0;
}


/*****************************main******************************/
/** @return 100 cannot open the file
 *  @return 101 cannot read name of file
 */
int main(int argc,char *argv[])
{  
    Quote_t* quote=creatQuote();
    //read file
    if(readRegals(&quote))
    {
        printf("Nespravny vstup.\n");
        clearQuote(quote);
        return 0;
    }

    if(commodity(quote,0))
    {
        printf("Nespravny vstup.\n");
        clearQuote(quote);
        return 0;
    }
    //free all memory
    clearQuote(quote);
    return 0;
}