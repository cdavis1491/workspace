
#include <stdio.h> // printf(),fopen(),fclose(),fscanf(),fprintf()
#include <stdlib.h> // exit()
#include <omp.h>
#define CHUNKSIZE 100

/* 
--------------------
---**PROTOTYPES**---
--------------------
*/



/* 
--------------
---**MAIN**---
--------------
*/
int main()
{
	int snap; 
	int maxsnap = 86; //change this as needed only doing one snap right now
	//loop over snapshots
	for (snap = 85; snap < maxsnap; snap++){
		//open newhalos_xxx.txt
		char filename[50];
		sprintf(filename, "/fs0/illustris_snapshots/HPC_testfiles/newhalos_%d.txt", snap);
		FILE *fp_in 
		fp_in = fopen(filename, "r");
		
		//check to make sure file opened
		if ( fp_in == NULL ) {
      		printf("input_file.txt not opened, exiting...\n");
      		exit(0);
    	}
    	
    	int Nhalos = 0;  
    	//the number of lines in the file will be equal to the number of halos. 
    	//this tells me how long my NEWdeepID_array and hostHalo arrays need to be
		int ch;
		while(!feof(fp_in))
		{
			ch = fgetc(fp_in);
			if(ch == '\n')
			{
				Nhalos++;
			}
		}
    	
    	printf("number of halos in the file was %d\n", Nhalos);
    	//allocate/initialize arrays for NEWdeepID 
    	//NEWdeepID gives the manodeep assigned haloID (int)
    	//int * NEWdeepID_array = malloc(Nhalos * sizeof(int));
    	
    	//allocate/initialize arrays for hostHalo 
    	//hostHalo says which FOF name the current halo belongs to 
    	//if 0 then it IS the FOF 
    	//int * hostHalo = malloc(Nhalos * sizeof(int));

    	//first line is header so actual number of elements is 1 less than
    	//the number of lines.  
    	//Nhalos = Nhalos - 1 
		
		//unpack first column = NEWdeepID 
		//unpack second column = hostHalo 
		

		//print 'starting snap blah'
		//create substructure array
		//call substructure function to fill array
		//print substructure array to file
	}
	return 0;
}



/* 
-------------------
---**FUNCTIONS**---
-------------------
*/


















//doop