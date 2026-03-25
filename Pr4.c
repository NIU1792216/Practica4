#include <stdio.h>
#include <stdlib.h>

double valors[] = { 5.6, 6.1, 1.2 , 2.3 , 9.8 };

int comparacio (const void * a, const void * b) {
    if(*(double*)a<*(double*)b) return 1;
    else return -1;
}

int main () {
   int n;

   printf("La llista abans d'ordenar es: \n");
   for( n = 0 ; n < 5; n++ ) {
      printf("%g ", valors[n]);
   }
   printf("\n");

   qsort(valors, 5, sizeof(double), comparacio);

   printf("Despres d'ordenar, la llista es: \n");
   for( n = 0 ; n < 5; n++ ) {   
      printf("%g ", valors[n]);
   }
   printf("\n");
   
   return(0);
}
