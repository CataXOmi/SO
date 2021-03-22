/*
Problema F14 Fisiere

F14. (3 puncte) Scrieti un program care numara aparitiile unui string
 intr-un fisier dat. Stringul si specificatorul fisierului sunt dati ca
 argumente in linia de comanda.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
 if (argc != 3)
   	{
   	 fprintf(stderr, "Utilizare: %s string fisier\n", argv[0]);
   	 return 1;
   	}
   	
 char *sir = argv[1];
 char *nume_fis = argv[2];
 FILE *fin = fopen(nume_fis,"r");
 
 if (!fin)
 	{
 	 //fprintf(stderr, "Fisierul %s nu s-a putut deschide\n", nume_fis);
         perror(nume_fis);
         return 1;
        }
 
 fseek(fin, 0, SEEK_END); 
 long lungime_fis = ftell(fin);
 fseek(fin, 0, SEEK_SET);
 long lungime_sir = strlen(sir);
 
 if (lungime_sir == 0)
 	{
 	 printf("Numarul de aparitii ale stringului \"%s\" in fisierul %s este 0\n", sir, nume_fis);
 	 fclose(fin);
 	 return 0;
 	}
 
 // aba
 // ababaa
 
 long poz = 0; // este un offset care-mi spune de unde vreau sa citesc
 long counter = 0;
 char *buf = (char*)malloc(lungime_sir+1);
 
 if(!buf)
 	{
 	 perror("malloc error");
 	 fclose(fin);
 	 return 1;
 	}
 	
 buf[lungime_sir] = '\0';
 
 while (poz+lungime_sir<=lungime_fis)
 {  
  //fseek(fin, lungime_sir-1, SEEK_CUR);
  
  fseek(fin, poz++, SEEK_SET);
  fread(buf, sizeof(char), lungime_sir, fin);
  if (strcmp(buf,sir)==0)
  	counter++;
 }
 
 printf("Numarul de aparitii ale stringului %s in fisierul %s este %ld\n", sir, nume_fis, counter);
 
 free(buf);
 fclose(fin); 
 return 0;
}
