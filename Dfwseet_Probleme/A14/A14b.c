/*

A14. (2 puncte) Scrieti niste programe care arata daca fii obtinuti cu system
 ai unui proces "p" mostenesc redirectarile intrari/iesirii standard care au
 loc daca lansam "p" in cadrul unui filtru:
     ... | p | ...

*/

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
 char sir_fiu[DIM+1];
 fread(sir_fiu, sizeof(char), DIM, stdin);
 //scanf("%s", sir_fiu);
 sir_fiu[DIM]='\0';
 fwrite(sir_fiu, sizeof(char), strlen(sir_fiu), stdout);
 //printf("%s", sir_fiu);  
 return 0;
}
