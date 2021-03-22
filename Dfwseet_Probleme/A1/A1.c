/*

A1. (2 puncte) Scrieti un program "copy" care se va lansa sub forma:
     copy   f1 + ... + fn    f
 (unde f1, ..., fn, f sunt fisiere) si are ca efect crearea lui f continand
 concatenarea lui f1, ..., fn; daca n=1 se copiaza f1 in f. Se vor folosi
 doar functiile de la nivelul inferior de prelucrare a fisierelor.

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

//#define dim_buf

int main(int argc, char *argv[])
{

 int fi, f;
 int i;
 
 if (argc % 2 == 0 || argc < 3)
   {
    fprintf(stderr, "Utilizare: %s f1[ + f2 + ... + fn] f\n", argv[0]);
    return 1;
   }
 
 for (i = 2; i<argc-1; i = i + 2)
    if (strcmp(argv[i],"+")!=0)
      {
       fprintf(stderr, "Utilizare: %s f1[ + f2 + ... + fn] f\n", argv[0]);
       return 1;
      }   
 
 if ((f = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY , S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
   {
    perror(argv[argc-1]);
    return 1;
   }
 
 //O_APPEND
 //masca implicita 022->negat 755
 //pt masca noua umask 0	
 for (i=1; i<argc - 1; i = i + 2) 
    {
	
	if ((fi = open(argv[i], O_RDONLY)) == -1)
	  {
           perror(argv[i]);
           close(f);
           return 1;
	  }
	
	/*int lung_sir = lseek(fi, 0, SEEK_END); 
	if (lung_sir==-1)
	  {
	   perror("lseek error");
	   close(f);
	   close(fi);
	   return 1;
	  }*/
	
	// memoria in o(1)
	
	char buf[1];
	int dim_buf = 1;
	/*char *buf = (char*)malloc(lung_sir+1);
 	if (!buf)
 	  {
 	   perror("malloc error");
 	   close(f);
 	   close(fi);
 	   return 1;
 	  }*/
	
	if (lseek(fi, 0, SEEK_SET)==-1) //aduc pointerul la inceput ca sa pot folosi read
	  {
	   perror(argv[i]);
	   close(f);
	   close(fi);
	   return 1;
	  }
	
	int char_citite;
	while ((char_citite = read(fi, buf, dim_buf)) != 0)
	     {
	      if (char_citite == -1)
	        {
	         perror(argv[i]); 
	         close(f);
	         close(fi);
	         return 1;
	        }
	     
	      if (write(f, buf, char_citite)==-1)
	        {
	         perror(argv[i]);
	         close(f);
	         close(fi);
	         return 1;
	        }
	     }
	close(fi);
	
	/*if (read(fi, buf, sizeof(char))==-1)
	  {
	   perror(argv[i]);
	   free(buf);
	   close(f);
	   close(fi);
	   return 1;
	  }
	
	if (write(f, buf, lung_sir)==-1)
	  {
	   perror(argv[i]);
	   free(buf);
	   close(f);
	   close(fi);
	   return 1;
	  }*/
	
	//free(buf);
	
	/*if (close(fi)==-1)
          {
           perror("close error");
           //return 1;
          }*/
        
    }
    
 close(f);
 return 0;
 
 /*if (close(f)==-1)
   {
    perror("close error");
    //return 1;
   }*/
 
}

