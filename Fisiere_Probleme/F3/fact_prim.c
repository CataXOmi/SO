/*
Problema F3 Fisiere

F3. (2.5 puncte) Scrieti un program care primeste ca argument in linia de
 comanda un intreg si afisaza descompunerea sa in factori primi.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{

   if (argc != 2)
   	{
   	 fprintf(stderr, "Utilizare: %s numar\n", argv[0]);
   	 return 1;
   	}
   	
   char* sir;
   long numar = strtol(argv[1], &sir, 10);
   
   if(*sir != '\0' || *argv[1] == '\0')
   	{
   	 fprintf(stderr, "Argumentul %s este incorect\n", argv[1]);
   	 return 1;
   	}
   
   if(numar < 0)
   	{
   	 numar = numar*(-1);
   	}
   
   if(numar == 0 || numar == 1)
   	{
   	 printf("Numarul nu se poate descompune in factori primi\n");
   	 return 0;
   	}	
   
   int putere, fact = 2;
   printf("Descompunerea numarului este: ");
   
   while(numar > 1)
       {
        putere=0;
        while(numar % fact == 0)
           {
            putere = putere+1;
            numar = numar / fact;
           }
        if(putere) 
            {
             if(numar == 1) 
              {
               if(putere == 1)
                printf("%d\n", fact);
               else
                printf("%d^%d\n", fact, putere);
              }
             else
               {
                if (putere == 1)                 
                  printf("%d*", fact);
                else
                  printf("%d^%d*", fact, putere);  
               }
            }
        fact = fact + 1;
       }
   
   return 0;
}
