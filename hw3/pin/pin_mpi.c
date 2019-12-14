

//The PIN is 221 (nprocs = 40, time = 41.46 sec.) 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<mpi.h> 

int main(int argc, char *argv[]) {
  assert(argc==2);

  double stop = (double)atol(argv[1]);
  int result;
  int global_result; 
  double x; 
  int id;
  int p;
  double elapsed_time; 

  assert(stop >= 1.0);

  MPI_Init(&argc, &argv);

  MPI_Barrier(MPI_COMM_WORLD);
  elapsed_time = - MPI_Wtime(); 
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p); 
  
  result = 0;

  for (x = (double)id; x < stop; x += (double)p) {
    double tmp = sin(x);
    double tmp2 = tmp*tmp;
    int z = (int)(tmp2*10000.0);

    result = (result + z)%10000; // 0<=result<10000

    
#ifdef DEBUG
    printf("x=%lf, y=%lf, z=%d\n", x, y, z);
    printf("new result : %d\n", result);
    fflush(stdout);
#endif
  }

  MPI_Reduce(&result, &global_result, 1, MPI_INT, MPI_SUM, 0,
	     MPI_COMM_WORLD);
  global_result = global_result % 10000;

  MPI_Barrier(MPI_COMM_WORLD);
  elapsed_time += MPI_Wtime(); 
  
  MPI_Finalize();
  if(!id) printf("The PIN is %d (nprocs = %d, time = %.2f sec.)\n"
		 , global_result, p, elapsed_time); 
  fflush(stdout);

  return 0; 
}
