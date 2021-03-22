/*

(a) 2 programe, care se lanseaza de la terminale diferite de catre acelasi
    utilizator, obtinand astfel 2 procese; fiecare proces va citi de la
    tastatura PID-ul celuilalt.
    
6. (2 puncte) Cerinta (a). Fiecare proces trimite celuilalt 2000 SIGUSR1, apoi
    un SIGINT (care va determina terminarea procesului advers). Inainte de
    terminare, fiecare proces scrie cate semnale a trimis si cate a primit.

*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int nrrec=0, nremi=0;
pid_t pa;

void h1usr(int n)
 {
  if(signal(n, h1usr)==SIG_ERR)
  	{
         perror("Signal error");
         exit(1);
  	}
  ++nrrec;
 }
 
void h2int(int n)
{
 printf("\nAm trimis: %d\n",nremi);
 printf("Am primit: %d\n",nrrec);

 exit(0);
}
 
int main()
{
 int i;
 if (signal(SIGUSR1, h1usr)==SIG_ERR || signal(SIGINT, h2int)==SIG_ERR)
   {
    perror("Signal error");
    return 1;
   } 
 
 printf("PID propriu: %d\n",getpid());
 printf("PID advers: "); 
 scanf("%d",&pa);
 

 for(i=0;i<2000;++i)
  {
   if(kill(pa,SIGUSR1)==-1)
    {
     perror("Kill error");
     //return 1;
    }
   else   
    { 
     ++nremi;
     //pause()-> alternativ aka acelasi nr trimis-primit 
    }
  }
 
 while(1)
 {
  pause();
 }
 
 //kill(pa,SIGINT);
 
 printf("\nAm trimis: %d\n",nremi);
 printf("Am primit: %d\n",nrrec);
 
 return 0;
}
