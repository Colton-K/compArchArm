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

  /* begin = clock(); */
 
  /* Do matrix multiply */
  for(i = 0; i<XSIZE; i++) {
      for(j = 0; j<YSIZE; j++) {
          for (k=0; k<XSIZE; k++) {
              x[i][j] = x[i][j] + y[i][k] * z[k][j];
          }
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
