#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>


//The pin is 6937, (nthreads = 40, time = 13.80 sec.)
//The PIN is 6937 (nprocs = 40, time = 41.46 sec.)

//expects input numthreads first and then the pin 

int nthreads;
double stop;
int result;
pthread_mutex_t mutexresult; 


void * driver (void * arg) {
  int tid = *((int*) arg);
  int x;
  int local_result = 0; 
  for(x = (double)tid; x<stop; x+=nthreads){
    double tmp = sin(x);
    double tmp2 = tmp*tmp;
    int z = (int)(tmp2*10000.0);
    local_result = (local_result+z) %10000;
  }
  pthread_mutex_lock (&mutexresult);
  result = (result + local_result) %10000; 
  pthread_mutex_unlock(&mutexresult);
} 

int main(int argc, char *argv[]) {
  assert(argc==3); 
  nthreads = (int)atoi(argv[1]);
  assert(nthreads>=0);
  printf("nthreads: %d\n", nthreads);
  stop = (double)atol(argv[2]);
  printf("stop: %lf\n", stop);
  double elapsed_time; 
  assert(stop >= 1.0);

  pthread_t threads[nthreads];
  int tids[nthreads];

  struct timespec begin, end;

  clock_gettime(CLOCK_MONOTONIC, &begin);

  pthread_mutex_init(&mutexresult, NULL);
  for(int i = 0; i<nthreads; i++){
    tids[i] = i;
  }
  
  for(int i=0; i<nthreads; i++){
    pthread_create(threads+i, NULL, driver, tids + i);
  }
  for(int i = 0; i<nthreads; i++){
    pthread_join(threads[i], NULL); 
  }
  pthread_mutex_destroy(&mutexresult); 

  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed_time = end.tv_sec - begin.tv_sec;
  elapsed_time +=(end.tv_nsec - begin.tv_nsec)/1000000000.0;
  printf("The pin is %d, (nthreads = %d, time = %.2f sec.)\n", result, nthreads,
	 elapsed_time);

  return 0; 

}
