#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <mpi.h>
#define WORK_TAG 1
#define TERMINATE_TAG 2
#define RESULT_TAG 3
typedef long double T;
#define DATATYPE MPI_LONG_DOUBLE

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

T epsilon = LDBL_MIN*10, pi = M_PI, subintervalLength, subtolerance;
int count = 0, nprocs, rank, numWorkers, numTasks;

T f(T x) {
  T result = 0;

  for (int i=0; i<500; i++)
    result += pow(sin(x), i)/(i+1);
  return result;
}

/* Sequential function to recursively estimate integral of f from a to
 * b.  fa=f(a), fb=f(b), area=given estimated integral of f from a to
 * b.  The interval [a,b] is divided in half and the areas of the two
 * pieces are estimated using Simpson's rule.  If the sum of those two
 * areas is within tolerance of given area, convergence has been
 * achieved and the result returned is the sum of the two areas.
 * Otherwise the function is called recursively on the two
 * subintervals and the sum of the results returned.
 */
T integrate_seq(T a, T b, T fa, T fb, T area, T tolerance) {
  T delta = b - a;
  T c = a+delta/2;
  T fc = f(c);
  T leftArea = (fa+fc)*delta/4;
  T rightArea = (fc+fb)*delta/4;

  count++;
  if (tolerance < epsilon) {
    printf("Tolerance may not be possible to obtain.\n");
    return leftArea+rightArea;
  }
  if (fabsl(leftArea+rightArea-area)<=tolerance) {
    return leftArea+rightArea;
  }
  return integrate_seq(a, c, fa, fc, leftArea, tolerance/2) +
    integrate_seq(c, b, fc, fb, rightArea, tolerance/2);
}

/* Sequential algorithm to estimate integral of f from a to b within
 * given tolerance. */
T integral_seq(T a, T b, T tolerance) {
  count = 0;
  return integrate_seq(a, b, f(a), f(b), (f(a)+f(b))*(b-a)/2, tolerance);
}

/* Worker function: called by procs of non-0 rank only.  Accepts
 * task from manager.   Each task is represented by a single integer
 * i, corresponding to the i-th subinterval of [a,b].  The task is
 * to compute the integral of f(x) over that subinterval within
 * tolerance of subtolerance. */
T worker(T a) {
  T left, right, result, answer;
  int task, taskCount = 0;
  MPI_Status status;
  MPI_Request recv_req;
  MPI_Request send_req;
  while (1) {
    MPI_Irecv(&task, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &recv_req);
    MPI_Wait(&recv_req, &status); 
    //WAIT IMMEDIATELY 
    if (status.MPI_TAG == WORK_TAG) {
      taskCount++;
      left = a+task*subintervalLength;
      right = left+subintervalLength;
      result = integral_seq(left, right, subtolerance);
      MPI_Isend(&result, 1, DATATYPE, 0, RESULT_TAG, MPI_COMM_WORLD,&send_req);
    } else {
      break;
    }

   
  }

  //wait for send right here
  MPI_Wait(&send_req, &status); 
  printf("Worker %d finished after completing %d tasks.\n", rank, taskCount);
  fflush(stdout);
  return 0.0;
}

/* manager: this function called by proc 0 only.  Distributes tasks
 * to workers and accumulates results.   Each task is represented
 * by an integer i.  The integer i represents a subinterval
 * of the interval [a,b].   Returns the final result.
 */

//HAVE RESULTS ARRAY THAT IS SIZE OF NUMPROCS
//RESULT IS NUMPROCS + NEXT_INDEX
T manager() {
  int i, task = 0;

  int * tasks = (int *)malloc(sizeof(int)*(nprocs-1));
  for(int z = 0; z<(nprocs-1); z++) tasks[z] = 0; 
  MPI_Status status;
  MPI_Request *recv_req = (MPI_Request *)malloc((nprocs-1)*sizeof(MPI_Request));
  MPI_Request *send_req = (MPI_Request *)malloc((nprocs-1)*sizeof(MPI_Request)); 
  T * results = (T*)malloc((nprocs-1)*sizeof(T));
  for(int j = 0; j<nprocs-1; j++) results[j] = 0.0; 
  T answer = 0.0;
  int next_index; 
  
    
  for (i=1; i<nprocs; i++) {
    tasks[i-1] = task; 
    MPI_Isend(&tasks[i-1], 1, MPI_INT, i, WORK_TAG,
	      MPI_COMM_WORLD, &send_req[i-1]);
    task++;
  }
  for(i=1; i<nprocs; i++){
    MPI_Irecv(results+i-1, 1, DATATYPE, MPI_ANY_SOURCE,
	      RESULT_TAG, MPI_COMM_WORLD, &recv_req[i-1]);
  }

  
  while (task < numTasks) {
    MPI_Waitany((nprocs-1),recv_req,&next_index, &status);
    answer += results[next_index];
    task++;
    tasks[next_index] = task; 
    MPI_Isend(&task, 1, MPI_INT, next_index+1, WORK_TAG, MPI_COMM_WORLD, &send_req[next_index]);
    MPI_Irecv(results+next_index, 1, DATATYPE, MPI_ANY_SOURCE, RESULT_TAG, MPI_COMM_WORLD,
	      &recv_req[next_index]);
  }

  
  for (i=1; i<nprocs; i++) {
    //wait any here
    MPI_Waitany((nprocs-1),recv_req, &next_index, &status); 
    MPI_Isend(NULL, 0, MPI_INT, next_index+1, TERMINATE_TAG, MPI_COMM_WORLD, &send_req[next_index]);
    answer += results[next_index];
  }
  free(results);
  free(tasks); 
  free(recv_req);
  free(send_req); 
  return answer;
}

/* called in collective fashion */
T integral(T a, T b, T tolerance) {
  numWorkers = nprocs - 1;
  numTasks = 200;
  subintervalLength = (b-a)/numTasks;
  subtolerance = tolerance/numTasks;
  if (rank == 0)
    return manager();
  else 
    return worker(a);
  MPI_Barrier(MPI_COMM_WORLD);
}

int main() {
  T result;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  result = integral(0, pi/2, 1e-10);
  if (rank == 0) printf("%4.20Lf\n", result);
  MPI_Finalize();
}
