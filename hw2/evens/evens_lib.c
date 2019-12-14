/* Implementation of the evens library. */
#include <stdio.h>
#include <stdlib.h>
#include "evens_lib.h"
// add other #includes as needed

int * find_evens(int * p, int n, int * num_evens) {
  int evens_count = 0; 
  for(int i = 0; i<n; i++)
    if(p[i]%2 == 0) evens_count++;

  *num_evens = evens_count; 

  if(evens_count==0) return NULL; 

  int *evens_arr = malloc(evens_count*sizeof(int));
  
  for(int i = 0; i<n; i++){
    if(p[i]%2 == 0){
      evens_arr[*num_evens - evens_count] = p[i];
      evens_count--; 
    }
  }
  return evens_arr; 
}

void print_array(int * p, int n) {
  printf("The even numbers are: ");
  for (int i = 0; i < n; i++)
    printf("%d ", p[i]);
  printf("\n");
  fflush(stdout);
}
