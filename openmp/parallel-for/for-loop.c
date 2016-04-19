#include <omp.h>
#define CHUNKSIZE 100
#define N     1000

int main ()  
{

   int i, chunk;
   float a[N], b[N], c[N];

   /* Some initializations */
   for (i=0; i < N; i++)
      a[i] = b[i] = i * 1.0;
   chunk = CHUNKSIZE;
   #pragma omp parallel shared(a,b,c,chunk) private(i)
   {

      int tid = omp_get_thread_num();

      #pragma omp for schedule(dynamic,chunk) nowait
      for (i=0; i < N; i++)
      {
         printf("thread id: %d, i: %d\n",tid,i);
         c[i] = a[i] + b[i];
      }

   }  /* end of parallel section */

   return 0;

}

   //a, b, c and chunk are all occupying the same memory space. where i is private 
   //it gets it's own memory space. 
   //in general arrays are going to be shared
   //chunk size is the size you give to schedule clause. it's chunks of a for loop that you're wanting each thread to process
   //if we execute with 8 threads we see all threads except 2 process 100 and 2 threads process 200 
   //dynamic means it is deciding where to assign threads as threads arrive instead of at compile time
   //static means that it is assigned at compile time instead of just whichever thread gets to it first
   //by default a forloop will wait at the end of the loop until all threads are finished.
   //nowait keeps the finished threads from waiting for the other threads and they can continue on to the next loop
   //guided is the same as dynamic but it shrinking the size of your chunk as you move farther in your processing
//user time is effectively CPU time. amount of time CPU is doing work 
//real is the wall time from start to finished
//if real time and user time are very close to gether that's indicitive that the program is CPU bound. 
//if real time > user time and sys time it means that there's some overhead introduced from having to create the threads. could also indicate your program is IO bound. the CPU is not the bottleneck 
//if user time > real time : if you have it split up on multiple CPU's it's summing up time across CPUs. 
