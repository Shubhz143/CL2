#include<iostream.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#define YES 1
#define NO 0

class string
{ int valid,noOfSymbols;
  char clause[10],symbol1[10],symbol2[10],InputString[30];
  public:
	string(){ valid=NO;noOfSymbols=1;
		  for(int i=0;i<11;i++)
		  { clause[i]=symbol1[i]=symbol2[i]='\0';}
		}
void getdata();
void input();
int validate();
friend CheckClauses(string,string);
friend Algo(string,string);
};
char * Unify(char L1[],char L2[]);

Algo(string s1,string s2)
 { char S[20]="",substr[40]="";
   if(s1.noOfSymbols!=s2.noOfSymbols)
   { cout<<"\nERROR:Two clauses entered by u were not having same number of argument!";
     getch();
     exit(1);
   }
   strcpy(S,Unify(s1.symbol1,s2.symbol1));//for Ist argument
   if(!strcmp(S,"FAIL"))
   { cout<<S;getch();exit(1);}
     if(strcmp(S,"NIL"))
     { char before[10],after[10];
       for(int i=0;S[i]!='/';i++)
	  { before[i]=S[i];}
       before[i]='\0';i++;	
       for(int j=0;S[i]!='\0';j++,i++)
       after[j]=S[i];
       after[j]='\0';

       if(!strcmp(s1.symbol1,after)) 
	  strcpy(s1.symbol1,before);
       if(!strcmp(s1.symbol2,after))
	  strcpy(s1.symbol2,before);

       if(!strcmp(s2.symbol1,after)) 
	  strcpy(s2.symbol1,before);
       if(!strcmp(s2.symbol2,after))
	  strcpy(s2.symbol2,before);

	  strcpy(substr,"),(");
	  strcat(substr,S);
	  strcat(substr,")");
     }
 
      strcpy(S,Unify(s1.symbol2,s2.symbol2));
      if(!strcmp(S,"FAIL"))
      { cout<<S;getch();exit(1);}
      if(strcmp(S,"NIL"))
      { char before[10],after[10];
	for(int i=0;S[i]!='/';i++)
	before[i]=S[i];
	before[i]='\0';
	i++;	              
	for(int j=0;S[i]!='\0';j++,i++)
	after[j]=S[i];
	after[j]='\0';
       if(!strcmp(s1.symbol2,after))
	  strcpy(s1.symbol2,before);
       if(!strcmp(s2.symbol2,after))
	  strcpy(s2.symbol2,before);
       strcat(S,substr);
   }
   cout<<"\nSUBSTITUTION:--> (";
   if(!strcmp(S,"NIL"))
   cout<<substr;
   else
   cout<<S;
   cout<<"\nL1:- "<<s1.clause<<"("<<s1.symbol1;
   if(s1.noOfSymbols==2)
   cout<<","<<s1.symbol2;
   cout<<")\n";
   cout<<"L2:- "<<s2.clause<<"("<<s2.symbol1;
   if(s2.noOfSymbols==2)
   cout<<","<<s2.symbol2;
   cout<<")\n";
 }

char * Unify(char L1[],char L2[])
{   char return_S[20];
  if(!strcmp(L1,L2)) 
   {
	strcpy(return_S,"NIL");
   }
  else if(isupper(L1[0]))
       {
	 if(strstr(L2,L1))
	   {
	    strcpy(return_S,"FAIL");
	   }
	  else
	   {
	    strcpy(return_S,L2);
	    strcat(return_S,"/");
	    strcat(return_S,L1);
	    return_S[(strlen(L1)+strlen(L2)+2)]='\0';
	   }
	}
  else if(isupper(L2[0]))
       {
	 if(strstr(L1,L2))
	   {
	    strcpy(return_S,"FAIL");
	   }
	  else
	   {
	    strcpy(return_S,L1);
	    strcat(return_S,"/");
	    strcat(return_S,L2);
	    return_S[(strlen(L1)+strlen(L2)+2)]='\0';
	   }
	}
    else
     {
      strcpy(return_S,"FAIL");
     }

   return(return_S);
}

CheckClauses(string s1,string s2)
 {
  return(!strcmp(s1.clause,s2.clause));
 }

void string::input()
{cout<<"\n Enter the Clause:- ";
 cin>>InputString;
 if(strstr(InputString,","))
 noOfSymbols=2;
}

void string::getdata()
 { int i=0;
  if(noOfSymbols==2)
  sscanf(InputString,"%s %s %s",&clause,&symbol1,&symbol2);
  else
  sscanf(InputString,"%s %s",&clause,&symbol1);
 }

int string:: validate()
 {
   int strLen,i=0;
   strLen=strlen(InputString);
   while(i<=strLen)
    { if(isalpha(InputString[i]))
      { while(InputString[i]!='\0')
	{ i++;
	  if(InputString[i]=='(')
	  { InputString[i]=' ';
	    i++;
	    if(isalpha(InputString[i]))
		{ i++;
	      while(InputString[i]!='\0')
	      { if(InputString[i]==')')
		{ InputString[i]=' ';
		  valid=YES;
		}
		else if(InputString[i]==',')
		{ InputString[i]=' ';
		  i++;
		  if(isalpha(InputString[i]))
		  { i++;
		    while(InputString[i]!='\0')
		    { if(InputString[i]==')')
		      { InputString[i]=' ';
			valid=YES;
		      }
		      i++;
		    }
		   }
		 }
		i++;
	       }
	     }
	   }
	 }
       }
     i++;
    }
   return(valid);
 }
main()
{
 int noOfsymbols=1;
 clrscr();
 string str1,str2;
 str1.input();
 if(!str1.validate())
 {cout<<"\nInvalid Input.\nIt should be in form:-> char/string(char/string[,char/string])";
  getch();
  exit(1);
 }
 str1.getdata();
 str2.input();
 if(!str2.validate())
 {cout<<"\nInvalid Input.\nIt should be in form:-> char/string(char/string[,char/string])";
  getch();
  exit(1);
 }
 str2.getdata();
 if(!CheckClauses(str1,str2))
  {
   cout<<"\nBoth literals are not equal so they cannot be unified!";
   getch();
   exit(1);
  }
	Algo(str1,str2);
	getch();
}
-----------------------------------------------output-------------------------------
Enter the Clause:- P(X,Y,Y)
Enter the Clause:- P(Y,Y,X)

SUBSTITUTION:--> (Y,X/Y,Y),(Y/X)
L1:- P(Y,Y,X)
L2:- P(Y,Y,X)
