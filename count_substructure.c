
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
		fp_in = fopen(filename, "r");
		//check to make sure file opened
		if ( fp_in == NULL ) {
      		printf("input_file.txt not opened, exiting...\n");
      		exit(0);
    	}
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