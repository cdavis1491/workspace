//*****************************************************************************
//
// This program calculates the product of a square matrix with itself:
//
// B = A * A
//
// Please keep all code in this single file.
//
//
//*****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void read_data_to_matrix(FILE *in_file, int N_count, int *func_matrix);

void matrix_mulitiplication(int *matrix_in, int *matrix_out, int N);

void print_matrix(int *matrix_in, int N);

int main(int argc, char ** argv)
{
   
   // check command line arguments
   if ( argc != 3 ) {
      printf("This program computes the product of n x n matrix with itself\n");
      printf("Usage: ./matrix_multiply filename n\n");
      exit(0);
   }

   // TODO: parse input arguments
   int i;
   i = 1;
   int matrix_dimension = 0;  //initialize variable for matrix size
   char * my_file = (argv[i]);
   ++i; 
   matrix_dimension = atoi(argv[i]);

   FILE *fp_in;
   fp_in = fopen(my_file,"r");
   if ( fp_in == NULL ) {
      printf("input_file.txt not opened, exiting...\n");
      exit(0);
   }
   

   // TODO: dynamically allocate space for matrix_A (input matrix) in 1d array
   int * matrix_A = malloc( matrix_dimension * matrix_dimension * sizeof(int));  // declare input matrix
   if ( matrix_A == NULL ) {
      printf("Allocation failed, exiting!\n");
      exit(0);
   }

   // TODO: call function to read data from file and copy into matrix_A
   read_data_to_matrix(fp_in, matrix_dimension, matrix_A);
   //for (i=0; i<matrix_dimension*matrix_dimension; i++) {
   //   printf("i : %d, matrixA : %d\n", i, matrix_A[i]);
   //}

   // TODO: dynamically allocate space for matrix_B (output matrix) in 1d array
   int * matrix_B = malloc( matrix_dimension * matrix_dimension * sizeof(int));  // declare output matrix
   if ( matrix_B == NULL ) {
      printf("Allocation failed, exiting!\n");
      exit(0);
   }
   // TODO: call function to perform matrix multiplication ( matrix_B = matrix_A * matrix_A )
   
   matrix_mulitiplication(matrix_A, matrix_B, matrix_dimension);

   // TODO: call function to write results (matrix_B) to stdout
   //   print_matrix(matrix_B, matrix_dimension);

   // TODO: free space allocated for matrix_A and matrix_B
   free(matrix_A);
   free(matrix_B);
   fclose(fp_in);
   return 0;

}

//FUNCTIONS

void read_data_to_matrix(FILE *in_file, int N_count, int *func_matrix) {
   int i; 
   for(i = 0; i<N_count*N_count; i++) {
      fscanf(in_file, "%d", &func_matrix[i]);
   }
}

void matrix_mulitiplication(int *matrix_in, int *matrix_out, int N){
   int row;
   int col;
   int k;
   int element;

#pragma omp parallel for shared(matrix_in,matrix_out,N) private(row,col,k) schedule(dynamic,10)
   for(row=0; row< N; row++){ 
      for(col=0; col<N; col++){
         element = 0;
         for(k=0; k<N; k++){
            element += matrix_in[row*N + k] * matrix_in[k*N + col];
         matrix_out[col + row*N] = element;
         }
      }
   }
}


void print_matrix(int *matrix_in, int N){
   int i;
   printf("Matrix B is: \n");
   for (i=0; i<(N*N); i++) {
      if ((i+1) % N == 0){
         printf("%d \n", matrix_in[i]);
      }
      else{
         printf("%d ", matrix_in[i]);
      }
   }   
}
