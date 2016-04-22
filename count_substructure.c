
#include <stdio.h> // printf(),fopen(),fclose(),fscanf(),fprintf()
#include <stdlib.h> // exit()
#include <omp.h>

/* 
--------------------
---**PROTOTYPES**---
--------------------
*/

void count_subs(long int  * Nhalos, long long int * NEWdeepID_array, long long int * hostHalo_array, long long int * substructure_array);


/* 
--------------
---**MAIN**---
--------------
*/
int main()
{
	int snap; 
	int maxsnap = 135; //change this as needed (max: 135)
	int minsnap = 30; //change this as needed (min: 30)
	//loop over snapshots
	for (snap = minsnap; snap < maxsnap; snap++){
		//open newhalos_xxx.txt
		char filename[50];
		sprintf(filename, "/fs0/illustris_snapshots/HPC_testfiles/newhalos_%d_nohead.txt", snap);
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
		rewind(fp_in);
    	//allocate/initialize arrays for NEWdeepID 
    	//NEWdeepID gives the manodeep assigned haloID (int)
    	long long int * NEWdeepID_array = malloc((Nhalos+10)* sizeof(long long int));
    	
    	//allocate/initialize arrays for hostHalo 
    	//hostHalo says which FOF name the current halo belongs to 
    	//if 0 then it IS the FOF 
    	long long int * hostHalo_array = malloc((Nhalos+10)* sizeof(long long int));

		//unpack columns from text file into arrays
		long int i;
		float junkarray_float[10];
		long long int junkarray_int[10];
		
		//these are garbage placeholders for reading the file

		for (i=0; i<Nhalos; i++){
			fscanf(fp_in, "%lli", &NEWdeepID_array[i]);
			fscanf(fp_in, "%lli", &hostHalo_array[i]);
			fscanf(fp_in, "%lli", &junkarray_int[0]);
			fscanf(fp_in, "%f", &junkarray_float[0]);
			fscanf(fp_in, "%lli", &junkarray_int[1]);
			fscanf(fp_in, "%f", &junkarray_float[1]);
			fscanf(fp_in, "%f", &junkarray_float[2]);
			fscanf(fp_in, "%f", &junkarray_float[3]);
			fscanf(fp_in, "%f", &junkarray_float[4]);
			fscanf(fp_in, "%f", &junkarray_float[5]);
			fscanf(fp_in, "%f", &junkarray_float[6]);
			fscanf(fp_in, "%f", &junkarray_float[7]);
			fscanf(fp_in, "%lli", &junkarray_int[2]);
			fscanf(fp_in, "%lli", &junkarray_int[3]);
			fscanf(fp_in, "%lli", &junkarray_int[4]);


		}

		//print 'starting snap blah'
		printf("Starting substructure on snapshot : %d \n", snap);

		//create substructure array
		long long int * substructure_array = malloc((Nhalos+10) * sizeof(long long int));

		//call substructure function to fill array
		count_subs(&Nhalos, NEWdeepID_array, hostHalo_array, substructure_array);
		//printf("Finished counting. Starting printing\n");

		//print substructure array to file
		int k; 
		char outfilename[50];
		sprintf(outfilename, "/fs0/illustris_snapshots/HPC_testfiles/substructure_output_%d.txt", snap);
		FILE *fp_out;
		fp_out = fopen(outfilename, "w");
		for (k = 0; k < Nhalos; k++){
			fprintf(fp_out, "%lli	%lli \n", NEWdeepID_array[k], substructure_array[k]);
		}

		fclose(fp_out);
		fclose(fp_in);
	}
	return 0;
}



/* 
-------------------
---**FUNCTIONS**---
-------------------
*/

void count_subs(long int * Nhalos, long long int * NEWdeepID_array, long long int * hostHalo_array, long long int * substructure_array){
	printf("Starting count_subs. There are %lli halos.\n", *Nhalos);
	long int halo; 
	//loop over haloID 
	for (halo = 0; halo < *Nhalos; halo++){
		//initialize the number of subs for this halo to zero
		long long int numsubs = 0;
		//find the ID of the halo we are investigating substructure for
		long int current_halo = NEWdeepID_array[halo];
		//loop over hostHalo_array and look for matches. 
		int host; 
		for (host = 0; host < *Nhalos; host++){
			//check if the halo in hostHalo list matches the haloID 
			if (hostHalo_array[host] == current_halo){
				numsubs++;
			}
			else {
				continue;
			}
		}
		//now we've gone through the whole list so we have counted numsubs for this halo
		//fill substructure_array with numsubs 
		substructure_array[halo] = numsubs; 

	}
	return;
}
















//doop
