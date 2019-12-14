#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#ifndef MAX_DEPOSIT
#define MAX_DEPOSIT 10.00
#endif
#ifndef MAX_WITHDRAW
#define MAX_WITHDRAW 20.00
#endif



int ndeps = 5;
int nwith = 7; 
double balance = 53.25; 
pthread_mutex_t mutex;
pthread_cond_t barrier; 
void * depositor (void * arg){
  int * id = (int*)arg;
  int myid = *id; 
  while(true){
    double to_deposit = ((double)rand() * (MAX_DEPOSIT - 0)) / (double)RAND_MAX+0; 
    pthread_mutex_lock(&mutex);
    printf("Depositor %d waiting to deposit %.2f to account. Balance %.2f\n", myid, to_deposit, balance); 
    balance+= to_deposit;
    printf("Depositor %d deposited %.2f to account. New balance %.2f\n", myid, to_deposit, balance); 
    pthread_cond_signal(&barrier);
    pthread_mutex_unlock(&mutex);
  }
}


void * withdrawer (void * arg){
  int * id = (int*)arg; 
  int myid = *id; 
  while(true){
    double to_withdraw = ((double)rand() * (MAX_WITHDRAW - 0)) /(double)RAND_MAX+0; 
    pthread_mutex_lock(&mutex); 
    while(balance < to_withdraw){
      printf("Withdrawer %d: WAITING to withdraw %.2f from account. Balance = %.2f\n", myid, to_withdraw, balance);
      pthread_cond_wait(&barrier, &mutex); 
    }
    balance-= to_withdraw;
    printf("Withdrawer %d withdrew %.2f from account. New balance: %.2f\n",
	   myid, to_withdraw, balance); 
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char ** argv){

  assert(argc > 3);
  double base, power;
  balance = (double)atof(argv[1]); 
  ndeps = atoi(argv[2]);
  nwith = atoi(argv[3]);

  printf("running with Balance = %.2f, Deps = %d, With = %d\n", balance, ndeps, nwith); 
  srand(time(NULL)); 
  int tids_deps [ndeps];
  int tids_with [nwith]; 

  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&barrier, NULL); 
  for(int i = 0; i<ndeps; i++) tids_deps[i] = i;
  for(int i = 0; i<nwith; i++) tids_with[i] = i; 

  pthread_t dep_threads[ndeps];
  pthread_t with_threads[nwith];
  

  for(int i = 0; i<ndeps; i++)
    pthread_create(dep_threads+i, NULL, depositor, tids_deps+i);

  for(int i = 0; i<nwith; i++)
    pthread_create(with_threads+i, NULL, withdrawer, tids_with+i);

  for(int i = 0; i<nwith; i++)
    pthread_join(with_threads[i], NULL);

  for(int i = 0; i<ndeps; i++)
    pthread_join(dep_threads[i], NULL);

  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&barrier);

  return 0; 
  


}
