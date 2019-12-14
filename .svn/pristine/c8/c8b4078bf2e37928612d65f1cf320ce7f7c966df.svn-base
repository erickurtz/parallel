/* Numerical integration of function of a single variable,
 * using adaptive quadrature.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

typedef long double T;

T epsilon = LDBL_MIN*10; // machine tolerance
T pi = M_PI; // pi=3.14159265358979...
int count = 0; // number of calls to integrate

/* A crazy function to integrate */
T f(T x) {
  T result = 0;

  for (int i=0; i<500; i++)
    result += pow(sin(x), i)/(i+1);
  return result;
}
// some other functions you can try...
//T f(T x) { return sin(x*1e5); }
//T f(T x) { return x*sin(x*x)-(1-x)*sin(1-x*x); }
//T f(T x) { return .1 + 2*x - .3*x*x + 4*x*x*x -2.7*x*x*x*x + .01*x*x*x*x*x; }

/* Given two points on x-axis, a < b, as well as fa=f(a) and fb=f(b),
 * the area of the trapezoid defined by (a,0), (b,0), (a,f(a)), (b,f(b)),
 * and some tolerance, computes an approximation to the integral from
 * a to b that is within that tolerance of the exact result.
 */
T integrate(T a, T b, T fa, T fb, T area, T tolerance) {
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
  // if we can get each sub-area to be within tolerance/2
  // of exact, then their sum will be within tolerance
  // of exact...
  return integrate(a, c, fa, fc, leftArea, tolerance/2) +
    integrate(c, b, fc, fb, rightArea, tolerance/2);
}

T integral(T a, T b, T tolerance) {
  count = 0;
  return integrate(a, b, f(a), f(b), (f(a)+f(b))*(b-a)/2, tolerance);
}

int main() {
  printf("%4.20Lf\n", integral(0, pi/2, 1e-10));
  printf("Number of calls to integrate: %d\n", count);
}
