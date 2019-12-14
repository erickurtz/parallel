#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int MY_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype,
		void *recvbuf, int recvcount, MPI_Datatype recvtype,
		MPI_Comm comm){
  int i;
  int local_nprocs;
  MPI_Comm_size(comm, &local_nprocs); 
  MPI_Request *send_req = (MPI_Request*)
    malloc(local_nprocs*sizeof(MPI_Request));
  MPI_Request *rec_req = (MPI_Request*)
    malloc(local_nprocs*sizeof(MPI_Request));

  char * castsend = (char*) sendbuf;
  char * castrecv = (char*) recvbuf;

  int datasize;

  MPI_Type_size(sendtype, &datasize); 

  for(i=0; i<local_nprocs; i++){
    MPI_Isend(castsend+(i*sendcount*datasize), sendcount, sendtype, i,0,comm,&send_req[i]);
    MPI_Irecv(castrecv+(i*recvcount*datasize), recvcount,
	      recvtype, i, 0, comm,&rec_req[i]);
  }
  MPI_Waitall(local_nprocs, send_req, MPI_STATUSES_IGNORE);
  MPI_Waitall(local_nprocs, rec_req, MPI_STATUSES_IGNORE);
  return 0; 
}
