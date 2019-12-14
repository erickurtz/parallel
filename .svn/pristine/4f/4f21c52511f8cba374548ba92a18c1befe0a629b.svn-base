/* Program for ragged question */
#include <stdio.h>
#include<stdlib.h>
// add other #includes as needed

// TODO: create two global variables: 
//   1. lengths. Type: pointer-to-int
//   2. data. Type: pointer-to-pointer-to-int.


int * lengths;
int * * data;

//Main consumes a list of n integers from the command line, allocates memory
//and stores integers from 0 to arg[0], 0 to arg[1]... in a "ragged" 2d array.
//The values are printed and then the memory is freed.


int main(int argc, char **argv) {

  
  int arg_size = argc-1; 
  lengths = (int *)malloc(arg_size*sizeof(int)); //allocates lengths pointer
  data = malloc(arg_size * sizeof(int*)); //allocates first level of data

  
  int curr_data = 0;
  
  for(int i = 0; i<arg_size; i++){
    lengths[i] = atoi(argv[i+1]);
    data[i] = malloc(lengths[i] * sizeof(int));
    
    for(int j = 0; j<lengths[i]; j++){
      data[i][j] = curr_data;
      curr_data++;
      printf("%d ", data[i][j]);
      
    }
    printf("\n"); 
    
  }

  for(int i = 0; i < arg_size; i++){
    free(data[i]);
  }

  free(data);
  free(lengths); 
	 
  
  return 0;
}
