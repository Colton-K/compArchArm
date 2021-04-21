#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define SIZE 200

int B = 10;

int main(void) {

  int x[SIZE][SIZE];
  int y[SIZE][SIZE];
  int z[SIZE][SIZE];

  int i, j, k, kk, jj, jj_limit, kk_limit;
  
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

  /* Do blocking matrix multiply */
  for(jj=0; jj<SIZE; jj+=B){
    for(kk=0; kk<SIZE; kk+=B){
      if((jj+B) < SIZE) {
        jj_limit = jj + B;
      }else{
        jj_limit = SIZE;
      }
      if((kk+B) < SIZE) {
        kk_limit = kk + B;
      }else{
        kk_limit = SIZE;
      }
      for(i=0; i<SIZE; i=i+1) {
        for(j=jj; j<jj_limit; j=j+1) {
          r = 0;
          for(k=kk; k<kk_limit; k=k+1) {
            r = r + y[i][k] * z[k][j];
          }
          x[i][j] += r;
        }
      }
    }
  }

}
