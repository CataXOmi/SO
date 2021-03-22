/*

A13. (4 puncte) Scriet un program care verifica daca un numar apare sau nu
 intr-un vector (numarul se vectorul sunt dati ca argumente in linia de 
 comanda) printr-o strategie de tip divide et impera: se imparte vectorul in
 doua, apoi se initiaza cate un proces fiu care cauta numarul in fiecare
 jumatate, in aceeasi maniera; cele doua procese se desfasoara in paralel. 
 Fiecare subproces returneaza 0 = negasit, 1 = gasit. Fiecare proces nu se 
 termina pana nu i se termina toti fii si in final returneaza suma valorilor
 returnate de ei. Procesul initial trebuie in plus sa afiseze un mesaj de tip 
 "gasit"/"negasit".

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main (int argc, char *argv[])
{
 int i;
 
 if (argc < 2)
   {
    fprintf(stderr, "Utilizare: %s numar elemente_vector\n", argv[0]);
    return 11;
   }
   
 char* sir;
 long numar = strtol(argv[1], &sir, 10);
   
 if (*sir != '\0' || *argv[1] == '\0')
   {
    fprintf(stderr, "Argumentul %s este incorect\n", argv[1]);
    return 11;
   }
 
 if (argc == 2)
   {
    //printf("Numarul nu a fost gasit, vector vid");
    printf("negasit\n");
    return 0;
   }
        
int st = 0;
int dr = argc-3; // -3 deoarece am considerat ca indexii vectorului sunt de la 0

for (i=2;i<argc;i++)
   {
    strtol(argv[i], &sir, 10);  
    if (*sir != '\0' || *argv[i] == '\0')
   	   {
            fprintf(stderr, "Argumentul %s este incorect\n", argv[i]);
            return 11;
           }
    }       

while(st<=dr)  
{ 
 int mij = st+(dr-st)/2;
 long elem = strtol(argv[mij+2], &sir, 10);
           
 if (fork())
   {
    if (fork())
      {
       int ps1, ps2;
       
       wait(&ps1);
       wait(&ps2);
       
       int sum = 0;
       
       if (WIFEXITED(ps1) && WIFEXITED(ps2)) //verific daca fiul s-a terminat normal
         sum = WEXITSTATUS(ps1) + WEXITSTATUS(ps2);
       
       if (numar == elem)
         {
          sum+=1;
         }
       
       if (st == 0 && dr == argc-3)
         {
          if (sum)
           printf("gasit %d\n",sum);
          else 
           printf("negasit\n");
         }
         
       return sum;
      }
    else
      {
       // fiu drept
       st = mij + 1;

      } 
   }
 else
   {
    // fiu stang
    dr = mij-1;
    
   }   
}

 return 0;
 
}
