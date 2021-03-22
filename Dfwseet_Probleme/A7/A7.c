/*

A7. (2 puncte) Scrieti niste programe care arata daca fii obtinuti cu fork
 ai unui proces "p" mostenesc redirectarile intrari/iesirii standard care au
 loc daca lansam "p" in cadrul unui filtru:
     ... | p | ...
     
*/

//stty -tostop 

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define DIM 256 

int main () 
{
 
 if (fork())
   {
    //tata, PID fiu
    wait(NULL);
   }
 else
   {
    //fiu, 0
    char sir_fiu[DIM+1];
    fread(sir_fiu, sizeof(char), DIM, stdin);
    sir_fiu[strlen(sir_fiu)]='\0';
    fwrite(sir_fiu, sizeof(char), strlen(sir_fiu), stdout);
   }
 return 0;
}
