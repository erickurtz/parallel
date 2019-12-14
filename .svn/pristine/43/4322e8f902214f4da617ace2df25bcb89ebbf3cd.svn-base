#include<stdio.h>
#include<mpi.h>
#define INTERVALS 5000000000L
int main(int argc, char *argv[]) {
  
  long double area; 
  long double total_area = 0.0; 
  long double xi;
  long i;
  int id;
  int p;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  area = 0.0; 

  for (i=0; i<INTERVALS; i+=p) {
    xi=(1.0L/INTERVALS)*(i+0.5L);
    area += 4.0L/(INTERVALS*(1.0L+xi*xi));
  }
  
  MPI_Reduce(&area, &total_area, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
	     MPI_COMM_WORLD);

  MPI_Finalize();
  if(!id) printf("Pi is %20.17Lf\n", total_area);

  return 0; 
}
