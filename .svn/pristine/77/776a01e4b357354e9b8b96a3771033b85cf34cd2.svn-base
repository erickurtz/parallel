#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define NPINGS 1000000

int main (){
  int i;
  int id;
  int p;
  double t0, t1; 
  MPI_Status status; 
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p); 
  for(i = 1; i<p; i++){
    double diff = 0.0; 
    for(int j = 0; j<NPINGS; j++){
      if(id==0){
	t0 = MPI_Wtime();
	MPI_Send(NULL, 0, MPI_BYTE,i,99,MPI_COMM_WORLD); 
      }
      if(id == i){
	MPI_Recv(NULL, 0, MPI_BYTE,0,99,MPI_COMM_WORLD,&status);
	MPI_Send(NULL, 0, MPI_BYTE,0,99,MPI_COMM_WORLD);	
      }

      if(id==0){
	MPI_Recv(NULL, 0, MPI_BYTE,i,99, MPI_COMM_WORLD, &status);
	t1 = MPI_Wtime();

	diff += t1-t0; 	
      }
    }
    if(id == 0)
      printf("Average time to transmit between 0 and %d: %11.10f\n",
	     i,diff/NPINGS);
  }
  
  MPI_Finalize(); 
  return 0; 
} 
