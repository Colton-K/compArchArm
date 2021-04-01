#include <stdio.h>
#include <math.h>
#include <time.h>

#define XSIZE 160
#define YSIZE 160

int main(void) {

  int x[XSIZE][YSIZE];
  int y[XSIZE][YSIZE];
  int z[XSIZE][YSIZE];

  int i, j, k;
  
  int r;

  /* clock_t begin, end; */

  /* double time_spent; */

  /* Initialize y matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
      y[i][j] = i + j;
    }
  }

  /* Initialize z matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
	z[i][j] = i + j;
    }
  }

  /* begin = clock(); */
 
  /* Do matrix multiply */
  for(i = 0; i<XSIZE; i+=4) {
      for(j = 0; j<YSIZE; j+=4) {
          int r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0;
          for (k=0; k<XSIZE; k++) {
              r1 += y[i][k] * z[k][j];
              r2 += y[i][k] * z[k][j+1];
              r3 += y[i][k] * z[k][j+2];
              r4 += y[i][k] * z[k][j+3];
              r5 += y[i+1][k] * z[k][j];
              r6 += y[i+1][k] * z[k][j+1];
              r7 += y[i+1][k] * z[k][j+2];
              r8 += y[i+1][k] * z[k][j+3];
              r9 += y[i+2][k] * z[k][j];
              r10 += y[i+2][k] * z[k][j+1];
              r11 += y[i+2][k] * z[k][j+2];
              r12 += y[i+2][k] * z[k][j+3];
              r13 += y[i+3][k] * z[k][j];
              r14 += y[i+3][k] * z[k][j+1];
              r15 += y[i+3][k] * z[k][j+2];
              r16 += y[i+3][k] * z[k][j+3];
          }
          x[i][j] = r1;
          x[i][j+1] = r2;
          x[i][j+2] = r3;
          x[i][j+3] = r4;
          x[i+1][j] = r5;
          x[i+1][j+1] = r6;
          x[i+1][j+2] = r7;
          x[i+1][j+3] = r8;
          x[i+2][j] = r9;
          x[i+2][j+1] = r10;
          x[i+2][j+2] = r11;
          x[i+2][j+3] = r12;
          x[i+3][j] = r13;
          x[i+3][j+1] = r14;
          x[i+3][j+2] = r15;
          x[i+3][j+3] = r16;
      }
  }
  /* INSERT CODE HERE. */

  /* end = clock(); */

  /* time_spent = (double)(end - begin) / CLOCKS_PER_SEC; */
  
  /* printf("Time Spent on MM is:  %lf\n", time_spent); */

  /*
  // print matrices
  // X
  printf("X Matrix:\n");
  for (i = 0; i < XSIZE; i++) {
      for (j = 0; j < XSIZE; j++) {
          printf("%d ", x[i][j]);
      }
      printf("\n");
  }

  // Y
  printf("Y Matrix\n");
  for (i = 0; i < YSIZE; i++) {
      for (j = 0; j < YSIZE; j++) {
          printf("%d ", y[i][j]);
      }
      printf("\n");
  }

  // Z
  printf("Z Matrix\n");
  for (i = 0; i < XSIZE; i++) {
      for (j = 0; j < XSIZE; j++) {
          printf("%d ", z[i][j]);
      }
      printf("\n");
  }
  */

}
