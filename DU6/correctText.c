#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#endif /* __PROGTEST__ */

//is substring in string
int isIn(const char *text, const char **replace,int *start,const char *(*rep)[2])
{
}

int control(const char *(*replace)[2])
{
  int i=0;
  while (replace[i+1][0]!=NULL)
  {
    for(int j=i+1; replace[j][0]!=NULL;j++)
    {
      if(strstr(replace[j][0],replace[i][0])!=NULL || strstr(replace[i][0],replace[j][0])!=NULL)
      {
        return 1;
      }
    }
    i++;
  }
  return 0;
}

//change incorect word
char *change(const char * text, const char **word,int start,char *rep)
{

}
//find incorect words
char *find(const char *text,const char * (*replace)[2])
{
 

}

char * newSpeak ( const char * text, const char * (*replace)[2] )
{
  if(control(replace))
    return NULL;
  char *returnText;
  returnText=find(text,replace); 
  return  returnText;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };


  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };

  const char * tbl [][2] =
{ 
  { "murderer", "termination specialist" },
  { "failure", "non-traditional success" },
  { "specialist", "person with certified level of knowledge" },
  { "dumb", "cerebrally challenged" },
  { "teacher", "voluntary knowledge conveyor" },
  { "evil", "nicenest deprived" },
  { "incorrect answer", "alternative answer" },
  { "student", "client" },
  { NULL, NULL }
};

  
  
  newSpeak ( "teacherevilstudentdumbfailuremurderer", tbl );
  /*
  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );
*/
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
