#include <stdio.h>
#include <omp.h>

int main ()  
{

   int x;
   x = 0;

   #pragma omp parallel shared(x) 
   {

      #pragma omp critical (norace)   // try commenting this out and increasing thread count
      x = x + 1;

   }  /* end of parallel section */

   printf("x: %d\n",x);

   return 0;

}

//serializes to avoid race conditions
//no race is just a name we are giving to critical statement. 
//you'll reach a point where your OS doesn't support enough threads (between 1000 and 10000) 
//use a low thread count to avoid race condition. 
