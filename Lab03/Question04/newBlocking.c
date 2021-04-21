#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define SIZE 400

// blocking code
int B = 10;

// caching code
#define CACHE_SIZE 65536
#define BLOCK_SIZE 8 // # of 32 bit long words
#define NUM_BLOCKS CACHE_SIZE/(BLOCK_SIZE * 4) // 32 bits = 4 bytes
#define INDEX_MASK 0xFFE0 // = log2(NUM_BLOCKS) bits
#define OFFSET_MASK 0x1F
#define TAG_MASK 0xFFFFFFFFFFFF0000

/* #define CACHE_SIZE 131072 */
/* #define BLOCK_SIZE 16 // # of 32 bit long words */
/* #define NUM_BLOCKS CACHE_SIZE/(BLOCK_SIZE * 4) // 32 bits = 4 bytes */
/* #define INDEX_MASK 0x1FFC0 // = log2(NUM_BLOCKS) bits */
/* #define OFFSET_MASK 0x3F */
/* #define TAG_MASK 0xFFFFFFFFFFFE0000 */

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
            cache(&y[i][k]);
            cache(&z[k][j]);
          }
          x[i][j] += r;
          cache(&x[i][j]);
        }
      }
    }
  }

  printf("Hits: %u, Misses: %u, Miss rate: %f\n", hits, misses, (float)misses/(hits+misses));
}
