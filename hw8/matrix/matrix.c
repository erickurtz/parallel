#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

int n, m;
double result;
double ** a;


void init(int argc, char* argv[]) {
  assert(argc == 3);
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  result = 0.0;
  a = (double **)malloc(n*sizeof(*a));
  for (int i=0; i<n; i++) {
    a[i] = (double *)malloc(m*sizeof(*a[i]));
    for (int j=0; j<m; j++)
      a[i][j] = i*2.0 + j*1.0;
  }
}

/* 
 * Note that the L2-norm is calculated on a column.
 */
void update() {
  double norm;
  for (int j=0; j<m; j++) {
    norm = 0.0;
    for (int i=0; i<n; i++)
      norm = norm + a[i][j]*a[i][j];
    norm = sqrt(norm);
    result = result + norm;
  }

}

int main (int argc, char* argv[]) {
  clock_t begin = clock();
  init(argc, argv);
  update();

  clock_t end = clock(); 
  double time = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("%f\n", result);
#ifdef TIME 
  printf("Time: %.2f\n", time); 
#endif
  return 0;
}
