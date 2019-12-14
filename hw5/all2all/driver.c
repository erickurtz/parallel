#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#define TYPE int
#define MY_MPI_TYPE MPI_INT

int MY_Alltoall(void *sendbuf, int secondcout, MPI_Datatype sendtype,
		void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);


int main(){

  int nprocs;
  int myrank;
  int i; 

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  TYPE * send_buff;
  TYPE * recv_buff;  
  send_buff = (TYPE *)malloc(nprocs*sizeof(TYPE));
  recv_buff = (TYPE *)malloc(nprocs*sizeof(TYPE));


  int n;
  for(i =0; i<nprocs; i++) send_buff[i] = (TYPE)myrank; //init
  
  for(n = 0; n<nprocs; n++){
    if(myrank == n){
      printf("Proc %d sendning: ",myrank); 
      for(i = 0; i<nprocs; i++) printf( "%d ",send_buff[i]);
      printf("\n");
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD); 
  }
  MY_Alltoall(send_buff,1,MY_MPI_TYPE,
	      recv_buff, 1, MY_MPI_TYPE, MPI_COMM_WORLD);

  free(send_buff);

  for(n = 0; n < nprocs; n++){
    if(myrank==n){
      printf("Proc %d received: ", myrank);
      for (i=0; i<nprocs; i++) printf("%d ", recv_buff[i]);
      printf("\n");
      fflush(stdout); 
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  free(recv_buff);

  MPI_Finalize(); 

  return 0; 
}
