#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define imin(a,b) (a<b?a:b)



int n, m;
double result;
double * a;
double * dev_a;

void init (int argc, char* argv[]){  
  assert(argc == 3);
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  result = 0.0;
  
  a = (double *)malloc(n*m*sizeof(double));

  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++)
      a[i*m+j] = i*2.0 + j*1.0;
  }


}

__global__ void kernel(double *dev_a, int n, int m){
  int col = threadIdx.x + blockIdx.x * blockDim.x; 
  int row = threadIdx.y + blockIdx.y * blockDim.y; 

  dev_a[m*row+col] = dev_a[m*row+col] * dev_a[m*row+col];  
  //dev_a[m*row+col] = 0.0;
}

int main (int argc, char* argv[]){
  cudaEvent_t start, stop;
  cudaEventCreate(&start); 
  cudaEventCreate(&stop); 
  cudaEventRecord(start); 
  init(argc, argv);

  /*
  for(int i = 0; i< n; i++){
    
    printf("\n"); 
    for(int j = 0; j<m; j++){
      printf("%f ",a[i*m+j]);
    }
    
    } */
  dim3 dimBlock(16,16);
  
  int dimx = (int) ceil((double)n/dimBlock.x);
  int dimy = (int) ceil((double)m/dimBlock.y); 

  //  printf("dimx: %d, dimy: %d\n", dimx, dimy); 


  dim3 dimGrid(dimx,dimy);
  int size = n*m*sizeof(double); 
  cudaMalloc((void**)&dev_a, size); 
  cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);

  kernel<<<dimGrid,dimBlock>>>(dev_a, n,m);
  
  
  cudaError_t err = cudaGetLastError();
  if(err != cudaSuccess)
    printf("Error: %s\n", cudaGetErrorString(err));
  cudaMemcpy( a, dev_a, size, cudaMemcpyDeviceToHost);
  //printf("done gpu stuff\n"); 
  double total = 0.0; 
  
  for(int j = 0; j<m; j++){
    double temp = 0.0; 
    for(int i = 0; i<n; i++){
      temp+= a[i*m+j]; 
    }
    total+= sqrt(temp); 
  }
  cudaEventRecord(stop); 
  float secs = 0; 
  cudaEventElapsedTime(&secs, start, stop);
  secs = secs / 1000;

  printf("%f\n", total);
#ifdef TIME
  printf("Time: %.2f\n", secs);
#endif

  free(a); 
  cudaFree(dev_a); 
}
