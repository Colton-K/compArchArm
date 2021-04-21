#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define SIZE 200


int main(void) {

  int x[SIZE][SIZE];
  int y[SIZE][SIZE];
  int z[SIZE][SIZE];

  int i, j, k;
  
  int r;

  /* Initialize x matrix */
  for(i=0; i<SIZE; i++) {
    for(j=0; j<SIZE; j++) {
      x[i][j] = 0;
    }
  } 

  /* Initialize y matrix */
  for(i=0; i<SIZE; i++) {
    for(j=0; j<SIZE; j++) {
      y[i][j] = i + j;
    }
  }

  /* Initialize z matrix */
  for(i=0; i<SIZE; i++) {
    for(j=0; j<SIZE; j++) {
	    z[i][j] = i + j;
    }
  }

  /* Do matrix multiply */
  for(i=0; i<SIZE; i=i+1) {
    for(j=0; j<SIZE; j=j+1) {
      r = 0;
      for(k=0; k<SIZE; k=k+1) {
        r = r + y[i][k] * z[k][j];
      }
      x[i][j] = r;
    }
  }
}
