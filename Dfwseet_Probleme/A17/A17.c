/*
 
A17. (1 punct) Scrieti un program care sa verifice daca schimbandu-si valoarea
variabilei de environment PWD, functia getcwd returneaza acelasi director
curent.
 
*/
 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
 
int main()
 {
    char cwd[256], nwd[256], t[256], var[256];
    
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      {
       perror("getcwd error");
       return 1;
      }
      
    printf("Valoare returnata de getcwd: %s\n", cwd);
    printf("PWD=%s\n", (char *)getenv("PWD"));
    printf("Valoarea cu care se inlocuieste PWD: ");
    fgets(t, 251, stdin);//gets(t);
    strcpy(var, "PWD=");
    strcat(var, t);
    
    if (putenv(var)==-1)
      {
       perror("putenv error");
       return 1; 
      }
    
    printf("PWD=%s\n", (char *)getenv("PWD"));
    
    if (getcwd(nwd, sizeof(nwd)) == NULL)
      {
       perror("getcwd error");
       return 1;
      }
      
    printf("Valoare getcwd dupa modificarea PWD: %s\n", nwd);
    
    if (strcmp(nwd, cwd) == 0) 
       printf("Valoarea returnata nu se modifica\n");
    else 
       printf("Valoarea returnata se modifica\n");
   
   return 0;
 }
