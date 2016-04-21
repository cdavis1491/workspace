
#include <stdio.h> // printf(),fopen(),fclose(),fscanf(),fprintf()
#include <stdlib.h> // exit()
#include <omp.h>

/* 
--------------------
---**PROTOTYPES**---
--------------------
*/

void count_subs(int  * Nhalos, int * NEWdeepID_array, int * hostHalo_array, int * substructure_array);


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
		FILE *fp_in;
		fp_in = fopen(filename, "r");
		
		//check to make sure file opened
		if ( fp_in == NULL ) {
      		printf("input_file.txt not opened, exiting...\n");
      		exit(0);
    	}
    	
    	long int Nhalos = 0;  
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
    	
    	//allocate/initialize arrays for NEWdeepID 
    	//NEWdeepID gives the manodeep assigned haloID (int)
    	long int * NEWdeepID_array = malloc((Nhalos+10)* sizeof(long int));
    	
    	//allocate/initialize arrays for hostHalo 
    	//hostHalo says which FOF name the current halo belongs to 
    	//if 0 then it IS the FOF 
    	long int * hostHalo_array = malloc((Nhalos+10)* sizeof(long int));

    	//first line is header so actual number of elements is 1 less than
    	//the number of lines.  
    	Nhalos = Nhalos - 1;
		printf("number of halos in the file was %ld\n", Nhalos);
		
		//read the header 
		char buffer[100];
		fgets(buffer, 100, fp_in);

		printf("buffer is: %s\n", buffer);

		//unpack columns from text file into arrays
		int i;
		int *c4; 
		long int *c2, *c12, *c13, *c14; //these are garbage placeholders for reading the file
		float *c3, *c5, *c6, *c7, *c8, *c9, *c10, *c11;

		//check that i need to go to Nhalos + 1 
		for (i=0; i<Nhalos; i++){
			fscanf(fp_in, "%ld, %ld, %ld, %f, %d, %f, %f, %f, %f, %f, %f, %f, %ld, %ld, %ld, ",\
			 &NEWdeepID_array[i], &hostHalo_array[i], &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10, &c11, &c12, &c13, &c14);
		}

		int haloi; 
		for (haloi=0; haloi < 10; haloi++){
			printf("NEWdeepID_array element %ld : %ld\n", haloi, NEWdeepID_array[haloi]);
			printf("hostHalo_array element %ld : %ld\n", haloi, hostHalo_array[haloi]);
		}

		/*
		//print 'starting snap blah'
		printf("Starting substructure on snapshot : %d \n", snap);

		//create substructure array
		int * substructure_array = malloc(Nhalos * sizeof(int));

		//call substructure function to fill array
		count_subs(&Nhalos, NEWdeepID_array, hostHalo_array, substructure_array);

		//print substructure array to file
		int k; 
		char outfilename[50];
		sprintf(outfilename, "/fs0/illustris_snapshots/HPC_testfiles/substructure_output_%d.txt", snap);
		FILE *fp_out;
		for (k = 0; k < Nhalos; k++){
			fprintf(fp_out, "%d , %d \n", hostHalo_array[k], substructure_array[k]);
		}
		*/
	}
	return 0;
}



/* 
-------------------
---**FUNCTIONS**---
-------------------
*/

//can probably make snapshot and Nhalos pointers and pass by ref? 
//arrays are already passed by ref
void count_subs(int * Nhalos, int * NEWdeepID_array, int * hostHalo_array, int * substructure_array){
	printf("Starting count_subs. There are %d halos.\n", *Nhalos);
	int halo; 
	//loop over haloID 
	for (halo = 0; halo < *Nhalos; halo++){
		//initialize the number of subs for this halo to zero
		int numsubs = 0;
		//find the ID of the halo we are investigating substructure for
		int current_halo = NEWdeepID_array[halo];
		//loop over hostHalo_array and look for matches. 
		int host; 
		for (host = 0; host < *Nhalos; host++){
			//check if the halo in hostHalo list matches the haloID 
			if (hostHalo_array[host] == current_halo){
				numsubs++;
			}
			else{
				//not a match; continue
				continue; 
			}
		}
		//now we've gone through the whole list so we have counted numsubs for this halo
		//fill substructure_array with numsubs 
		substructure_array[halo] = numsubs; 
		if (halo%1000 == 0){
			printf("HaloID : %d\n", hostHalo_array[halo]);
			printf("Numsubs : %d\n", numsubs);
		}
	}
	return;
}
















//doop
