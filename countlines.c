#include <stdio.h> // printf(),fopen(),fclose(),fscanf(),fprintf()
#include <stdlib.h> // exit()


int main()
{
  long int testarray[4];
   FILE *fp_in;
   fp_in = fopen("input.txt","r");
   
   if ( fp_in == NULL ) {
      printf("input_file.txt not opened, exiting...\n");
      exit(0);
   }

   	int lines = 0; 
	int ch;
	while(!feof(fp_in))
	{
		ch = fgetc(fp_in);
		if(ch == '\n')
		{
			lines++;
		}
	}
	
	rewind(fp_in);


	int i; 
	long int array2[4], array3[4], array4[4]; 
	for (i=0; i<4; i++){
	  fscanf(fp_in, "%ld", &testarray[i]);
	  fscanf(fp_in, "%ld", &array2[0]);
	  fscanf(fp_in, "%ld", &array3[0]);
	  fscanf(fp_in, "%ld", &array3[1]);
	  printf("testarray element is : %ld\n", testarray[i]);
	
	}

	int count; 
	for (count=0; count<4; count++){
	  printf("count is %d and testarray is %ld\n", count,  testarray[count]);
	}

	printf("number of lines in the file was %d\n", lines);
	fclose(fp_in);
	return 0;
}


