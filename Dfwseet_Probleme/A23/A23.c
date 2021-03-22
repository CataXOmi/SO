/*

A23. (3 puncte) Scrieti un program "nrc" care se lanseaza sub forma:
     nrc   com
 unde "com" este o comanda externa (adica asociata unui fisier executabil de 
 pe disc) avand eventual si argumente in linia de comanda (deci com este un 
 sir de cuvinte) si care lanseaza comanda "com", numarand cuvintele scrise 
 de ea pe standard output. In acest scop procesul "nrc" creaza un tub fara
 nume, apoi se bifurca (cu "fork") a.i. intrarea standard a tatalui si iesirea 
 standard a fiului sa fie in acest tub, apoi fiul se inlocuieste (cu o functie
 din familia "exec") cu un proces ce executa "com".

*/

#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
 int d[2],i;
 char *argvnou[256];
 
 if (argc < 2)
   {
    fprintf(stderr, "Utilizare: %s com [arg1 arg2 ...]\n", argv[0]);
    return 1;
   }
 if (argc > 256)
   {
    fprintf(stderr, "Prea multe argumente\n");
    return 1;
   }
 for (i=1;i<=argc;i++)
    {
     argvnou[i-1] = argv[i];
    }
    
 if (pipe(d) == -1)
   {
    perror("pipe error");
    return 1;
   }
 
 if (fork())
   {
    close(STDIN_FILENO);
    
    
    if (dup(d[0]) == -1)
      {
       perror("dup error");
       wait(NULL);
       return 1;
      }
    
    close(d[0]);
    close(d[1]);
    
    
    // sa citeasca caracter cu caracter 
    
    char c;
    int nrcuv = 0;
    int in_cuvant = 0;
    
    while (scanf("%c", &c) != EOF)
         {
          if (!isspace(c))
            {
             if (in_cuvant == 0)
               {
                nrcuv++;
                in_cuvant = 1; 
               }
             
            }
           else
            {
             in_cuvant = 0;
            }
         }
    
    printf("%d\n",nrcuv);
    wait(NULL);
   }
  
 else
   {
    close(STDOUT_FILENO);
    
    if (dup(d[1]) == -1)
      {
       perror("dup error");
       return 1;
      }
    
    close(d[1]);
    close(d[0]);
    
    execv(argv[1],argvnou);
    
    perror(argv[1]);
    return 1;
   }
   
  
 return 0;
}
