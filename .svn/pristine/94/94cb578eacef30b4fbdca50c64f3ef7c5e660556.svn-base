/* Producer-consumer example. Single producer, single consumer, single datum.
 *
 * Author: Stephen F. Siegel
 * Date : 2016-oct-24
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sem.h"

int niter = 10; // number of times to loop
semaphore sem1, sem2; // signals to read and write
int *buf; // the buffer
int num_elem;
int prod_index, cons_index = 0; 

pthread_mutex_t mutex; 

void * producer(void * arg) {
  int value; // local var to store value produced
  while(1){
    value = rand(); // represents "producing" some value
    if(semaphore_P(&sem1)){ // wait for signal from consumer: safe to write
      buf[prod_index] = value;
      printf("Producer: produced %d at index %d\n", value,prod_index);
      fflush(stdout);
      prod_index = (prod_index+1)%num_elem;
      semaphore_V(&sem2); // signal to consumer: safe to read
    }else{
      semaphore_V(&sem2); // signal to consumer: safe to read
      printf("prod waiting...localindex = %d\n",prod_index); 
    }
  }
  return NULL;
}

void * consumer(void * arg) {
  int value; // local var to store value consumed
  
  while(1){    
    if (semaphore_P(&sem2)){ // wait for signal from producer: safe to read]); 
      value = buf[cons_index];
      printf("Consumer: read %d at index %d\n", value,cons_index);
      cons_index = (cons_index+1)%num_elem; 

      fflush(stdout);
      semaphore_V(&sem1); // signal to producer: safe to write
    }else{
      semaphore_V(&sem1); // signal to producer: safe to write
      printf("cons waiting...localindex = %d\n",cons_index);  
    }
  }
  return NULL;
}



int main(int argc, char*argv[]) {
  assert(argc == 2);
  num_elem = atoi(argv[1]);

  buf = (int*)malloc(sizeof(int)*num_elem); 
  pthread_mutex_init(&mutex, NULL); 
  semaphore_init(&sem1, num_elem+1);
  semaphore_init(&sem2, 0);
  
  pthread_t producer_thread, consumer_thread;

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);
  semaphore_destroy(&sem1);
  semaphore_destroy(&sem2);
  pthread_mutex_destroy(&mutex); 
}
