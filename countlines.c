#include <stdio.h> // printf(),fopen(),fclose(),fscanf(),fprintf()
#include <stdlib.h> // exit()


int main()
{

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
	
	printf("number of lines in the file was %d\n", lines);

	return 0;
}


