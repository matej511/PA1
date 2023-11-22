#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem *m_Next;
  char *m_Name;
  char m_Secret[24];
} TITEM;

int cmpName(const TITEM *a, const TITEM *b)
{
  return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a, const TITEM *b)
{
  return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a, const TITEM *b)
{
  size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
  return (lb < la) - (la < lb);
}
#endif /* __PROGTEST__ */

TITEM *newItem(const char *name, TITEM *next)
{
  TITEM *newNode=(TITEM*)malloc(sizeof(TITEM));
  newNode->m_Name=(char*)calloc((int)strlen(name)+1,sizeof(char));
  strcpy(newNode->m_Name,name);
  for(int i=0; i<24; i++)
    newNode->m_Secret[i]='\0';
  newNode->m_Next=next;
  return newNode;

}

TITEM *parition(TITEM* first, TITEM* last, int asc, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *pivot=first;
  TITEM *front=first;
  char temp[200];
  while (front!=NULL && front!=last)
  {
    if(cmpFn(front,last)<=0 && asc==1)
    {
      pivot=first;
      strcpy(temp,first->m_Name);
      strcpy(first->m_Name,front->m_Name);
      strcpy(front->m_Name,temp);
      first=first->m_Next;

    }
    if(cmpFn(front,last)>0 && asc==0)
    {
      pivot=first;
      strcpy(temp,first->m_Name);
      strcpy(first->m_Name,front->m_Name);
      strcpy(front->m_Name,temp);
      first=first->m_Next;

    }
    front=front->m_Next;
  }
  strcpy(temp,first->m_Name);
  strcpy(first->m_Name, last->m_Name);
  strcpy(last->m_Name,temp);
  return pivot;
}

void quickSort(TITEM* first, TITEM* last,int asc, int (*cmpFn)(const TITEM *, const TITEM *))
{
  if(first==last)
    return;
  TITEM* pivot=parition(first,last, asc, cmpFn);
  if(pivot!=NULL && pivot->m_Next!=NULL)
    quickSort(pivot->m_Next,last,asc,cmpFn);
  if(pivot!=NULL && first!=pivot)
    quickSort(first,pivot,asc, cmpFn);
}


/*MERGESORT*/
TITEM* sortedMergeA(TITEM* a, TITEM* b,int (*cmpFn)(const TITEM *, const TITEM *));
TITEM* sortedMergeB(TITEM* a, TITEM* b,int (*cmpFn)(const TITEM *, const TITEM *));
void frontBackSplit(TITEM* source, TITEM ** front, TITEM** back);

void mergeSort(TITEM** headRef,int asc, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM* head= *headRef;
  TITEM* a;
  TITEM *b;

  if(head==NULL || head->m_Next==NULL)
    return;
  frontBackSplit(head,&a,&b);
  mergeSort(&a,asc,cmpFn);
  mergeSort(&b,asc, cmpFn);
  if(asc==0)
    *headRef=sortedMergeA(a,b,cmpFn);
  if(asc==1)
    *headRef=sortedMergeB(a,b,cmpFn);
}

TITEM* sortedMergeA(TITEM* a, TITEM* b, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *result=NULL;
  if(a==NULL)
    return b;
  if(b==NULL)
    return a;
  int cmp=cmpFn(a,b);
  if(cmp>=0)
  {
    result=a;
    result->m_Next=sortedMergeA(a->m_Next,b,cmpFn);
  }
  else
  {
    result = b;
    result->m_Next=sortedMergeA(a,b->m_Next,cmpFn);
  }
  return result;
}

TITEM* sortedMergeB(TITEM* a, TITEM* b, int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *result=NULL;
  if(a==NULL)
    return b;
  if(b==NULL)
    return a;
  int cmp=cmpFn(a,b);
  if(cmp<=0)
  {
    result=a;
    result->m_Next=sortedMergeB(a->m_Next,b,cmpFn);
  }
  else
  {
    result = b;
    result->m_Next=sortedMergeB(a,b->m_Next,cmpFn);
  }
  return result;
}

void frontBackSplit(TITEM* source, TITEM** front, TITEM** back)
{
  TITEM *fast=source->m_Next;
  TITEM* slow= source;
  while (fast!=NULL)
  {
    fast=fast->m_Next;
    if(fast!=NULL)
    {
      slow=slow->m_Next;
      fast=fast->m_Next;
    }
  }
  *front=source;
  *back=slow->m_Next;
  slow->m_Next=NULL;
}

/***************************************************************/




TITEM *sortListCmp(TITEM *l, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{

  //mergeSort(&l,ascending,cmpFn);
  TITEM *last=l;
  while (last->m_Next)
    last=last->m_Next;
  quickSort(l,last,ascending,cmpFn);
  
  return l;
}

void freeList(TITEM *src)
{
  while (src!=NULL)
  {
    TITEM* tmp=src->m_Next;
    free(src->m_Name);
    free(src);
    src=tmp;
  }
  
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  TITEM *l;
  char tmp[50];

  assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
  l = NULL;
  l = newItem("BI-PA1", l);
  l = newItem("BIE-PA2", l);
  l = newItem("NI-PAR", l);
  l = newItem("lin", l);
  l = newItem("AG1", l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName); 
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = newItem("AAG.3", l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen); 
  TITEM* f=l;
  while (f)
  {
    printf("%s\n",f->m_Name);
    f=f->m_Next;
  }
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  l = NULL;
  strncpy(tmp, "BI-PA1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "BIE-PA2", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "NI-PAR", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "lin", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AG1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  strncpy(tmp, "AAG.3", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
