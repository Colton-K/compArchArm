#include <stdio.h>
#include <math.h>

#define XSIZE 200
#define YSIZE 200

#define CACHE_SIZE 65536
#define BLOCK_SIZE 8 // # of 32 bit long words
#define NUM_BLOCKS CACHE_SIZE/(BLOCK_SIZE * 4) // 32 bits = 4 bytes
#define INDEX_MASK 0xFFE0 // = log2(NUM_BLOCKS) bits
#define OFFSET_MASK 0x1F
#define TAG_MASK 0xFFFFFFFFFFFF0000


/* printf("CACHE SIZE %u, BLOCK_SIZE %u, NUM_BLOCKS %u, INDEX_MASK %x \n", CACHE_SIZE, BLOCK_SIZE, NUM_BLOCKS, INDEX_MASK); */

int hits = 0;
int misses = 0;

int validBit[NUM_BLOCKS];
int tag[NUM_BLOCKS];

void cache(void * addr) {
    /* printf("%p \n", addr); */
    int index = ((unsigned long)addr & (unsigned long)INDEX_MASK) >> 5;
    // also shift?

    int currTag = ((unsigned long)addr & TAG_MASK) >> 16;
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


int main(void) {

  int x[XSIZE][YSIZE];
  int y[XSIZE][YSIZE];
  int z[XSIZE][YSIZE];

  int i, j, k;
  
  int r;

  /* Initialize validBit and tag matrix */
  for(i=0; i<NUM_BLOCKS; i++) {
    validBit[i] = 0;
    tag[i] = 0;
  }



  /* Initialize x matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
      x[i][j] = 0;
      /* printf("Initializing X[%u][%u]: %p \n", i, j, &x[i][j]); */
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
  for(i=0; i<XSIZE; i=i+1) {
    for(j=0; j<YSIZE; j=j+1) {
      r = 0;
      for(k=0; k<XSIZE; k=k+1) {
        r = r + y[i][k] * z[k][j];
        cache(&y[i][k]);
        cache(&z[k][j]);
      }
      x[i][j] = r;
      cache(&x[i][j]);
    }
  }
    
  printf("Hits: %u, Misses: %u, Miss rate: %f\n", hits, misses, (float)misses/(hits+misses));
  /* printf("X Head: %p, Y Head: %p, Z Head %p \n", x, y, z); */
  /* printf("X[0] %p, X[1] %p, X[2] %p \n", x[0], x[1], x[2]); */
}
