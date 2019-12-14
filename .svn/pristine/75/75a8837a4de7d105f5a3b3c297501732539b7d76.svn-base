/* Driver for evens libary */
#include "evens_lib.h"
// add other #includes as needed

// ADD A GOOD COMMENT HERE.  Explain exactly what the
// main function does.
int main(int argc, char *argv[]) {

  int init_num_evens = 0;
  int * init_arr = malloc((argc-1)*sizeof(int));
  for(int i = 0; i<argc-1; i++){
    init_arr[i] = atoi(argv[i+1]); 
  }

  int * evens_arr;

  evens_arr = find_evens(init_arr, argc-1, &init_num_evens);

  print_array(evens_arr, init_num_evens);
  free(evens_arr);
  return 0;
}
