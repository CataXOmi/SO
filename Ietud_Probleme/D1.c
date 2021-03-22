/*

D1. (4 puncte) Program care primeste ca argument in linia de comanda un
 director si afiseaza arborescenta de directoare si fisiere cu originea
 in el (similar comenzii tree /f din DOS).

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void arborescenta(char *arb, long nivel)
{
 
 DIR *dir_curent = opendir(arb);
 
 if (dir_curent == NULL)
   {
    perror(arb);
    exit(1);
   }
      
    if (nivel == 0)
       {
        printf("\x1B[34m%s\n\x1B[37m", arb);
        nivel++;
       }
    struct dirent *f_dir_curent;

    while ((f_dir_curent = readdir(dir_curent)) != NULL)
    	{
    	 
    	 if (strcmp(f_dir_curent->d_name, ".") == 0 || strcmp(f_dir_curent->d_name, "..") == 0)
                continue;

         int i;
         
         for (i=0; i<nivel; i++)
             printf("\x1B[31m|  ");
         
            
         if (f_dir_curent->d_type == DT_DIR)

             {
              printf("\x1B[34m%s\n\x1B[37m", f_dir_curent->d_name);
              int dim_dir = strlen(f_dir_curent->d_name);
              char *arb_nou = (char*)malloc(sizeof(char) * (strlen(arb) + dim_dir + 2));
	  
	       if (!arb_nou)
	         {
	          perror("malloc error");
	          closedir(dir_curent);
	          exit(1);
	        }    
	  	
              strcpy(arb_nou, arb);
              
              if(strcmp(arb_nou,""))
                if(arb_nou[strlen(arb_nou)-1] != '/')
                  strcat(arb_nou, "/");
              	
              
              strcat(arb_nou, f_dir_curent->d_name);
              arborescenta(arb_nou, nivel+1);
         
              free(arb_nou);
             }
         else
             printf("\x1B[32m%s\n\x1B[37m", f_dir_curent->d_name);
    	}
    closedir(dir_curent);
   
}

int main(int argc, char* argv[])
{
 if (argc != 2)
   	{
   	 fprintf(stderr, "Utilizare: %s director\n", argv[0]);
   	 return 1;
   	}
 
 char *nume = argv[1];
 
 arborescenta(nume,0);
 
 return 0;
}
