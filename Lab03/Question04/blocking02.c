#include <stdio.h>
#include <math.h>

#define XSIZE 200
#define YSIZE 200

/* #define BLOCKSIZE 36 */
#define BLOCKSIZE 104

#define CACHE_SIZE 131072
#define BLOCK_SIZE 16 // # of 32 bit long words
#define NUM_BLOCKS CACHE_SIZE/(BLOCK_SIZE * 4) // 32 bits = 4 bytes
#define INDEX_MASK 0x1FFC0 // = log2(NUM_BLOCKS) bits
#define OFFSET_MASK 0x3F
#define TAG_MASK 0xFFFFFFFFFFFE0000


/* printf("CACHE SIZE %u, BLOCK_SIZE %u, NUM_BLOCKS %u, INDEX_MASK %x \n", CACHE_SIZE, BLOCK_SIZE, NUM_BLOCKS, INDEX_MASK); */

int hits = 0;
int misses = 0;

int validBit[NUM_BLOCKS];
int tag[NUM_BLOCKS];

void cache(void * addr) {
    /* printf("%p \n", addr); */
    int index = ((unsigned long)addr & (unsigned long)INDEX_MASK) >> 6;
    // also shift?

    int currTag = ((unsigned long)addr & TAG_MASK) >> 17;
    /* printf("addr: %p, Index: %u, currTag: %u, NUM_BLOCKS %u \n", addr, index, currTag, NUM_BLOCKS); */

    if (validBit[index]) {
        if (tag[index] == currTag) {
            hits++;
        }
        else {
            misses++;
            validBit[index] = 1;
            tag[index] = currTag;
        }
    }
    else {
        misses++;
        validBit[index] = 1;
        tag[index] = currTag;
    }
}

void printMatrix(int m[XSIZE][YSIZE]) {
    int i, j;
    for (i = 0; i < XSIZE; i++) {
        for (j = 0; j < YSIZE; j++) {
            printf("%u\t", m[i][j]);
        }
        printf("\n");
    }
}

void computeBlock(int n, int ii, int jj, int kk, int x[XSIZE][YSIZE], int y[XSIZE][YSIZE], int z[XSIZE][YSIZE]) {
    int i, j, k, q;
    
    for (i = ii; i < ii+BLOCKSIZE; i++) {
        for (j = jj; j < jj+BLOCKSIZE; j++) {
            if ((kk+BLOCKSIZE) < XSIZE) {
                q = kk + BLOCKSIZE;
            }
            else {
                q = XSIZE;
            }
            int r = x[i][j];
            /* int r = 0; */
            /* printf("i: %d, j: %d, r: %d \n", i, j, r); */
            for (k = kk; k < q; k++) {
                r = r + y[i][k] * z[k][j];
                cache(&y[i][k]);
                cache(&z[k][j]);
            }
            x[i][j] = r;
            cache(&x[i][j]);
        }
    }
}

int main(void) {

  int x[XSIZE][YSIZE];
  int y[XSIZE][YSIZE];
  int z[XSIZE][YSIZE];

  int i, j, k;
  
  int r;

  /* Initialize x matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
      x[i][j] = 0;
    }
  }

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

  /* Do matrix multiply */
  /* for(i=0; i<XSIZE; i=i+BLOCKSIZE) { */
  /*   for(j=0; j<YSIZE; j=j+BLOCKSIZE) { */
  /*     r = 0; */
  /*     for(k=0; k<XSIZE; k=k+BLOCKSIZE) { */
  /*       r = r + y[i][k] * z[k][j]; */
  /*     } */
  /*     x[i][j] = r; */
  /*   } */
  /* } */

  /* Do matrix multiply */
  for(i=0; i<XSIZE; i=i+BLOCKSIZE) {
    for(j=0; j<YSIZE; j=j+BLOCKSIZE) {
      for(k=0; k<XSIZE; k=k+BLOCKSIZE) {
        computeBlock(BLOCKSIZE, i, j, k, x, y, z);
      }
    }
  }

  /* printMatrix(x); */

  printf("Hits: %u, Misses: %u, Miss rate: %f\n", hits, misses, (float)misses/(hits+misses));
}
