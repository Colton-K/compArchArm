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

  clock_t begin, end;

  double time_spent;

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

  begin = clock();
 
  /* Do matrix multiply */
  for(i = 0; i<XSIZE; i+=2) {
      for(j = 0; j<YSIZE; j+=2) {
          int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
          for (k=0; k<XSIZE; k++) {
              r1 += y[i][k] * z[k][j];
              r2 += y[i+1][k] * z[k][j];
              r3 += y[i][k] * z[k][j+1];
              r4 += y[i+1][k] * z[k][j+1];
          }
          x[i][j] = r1;
          x[i+1][j] = r2;
          x[i][j+1] = r3;
          x[i+1][j+1] = r4;
      }
  }
  /* INSERT CODE HERE. */

  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  
  printf("Time Spent on MM is:  %lf\n", time_spent);

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
