#ifndef MUXDMUX_H
#define MUXDMUX_H

#include "vectoredBits.h"

struct bitVector** dmux(struct bitVector* input, int selector, int numWays);
struct bitVector* mux(struct bitVector** inputs, int selector);

struct bitVector** dmux(struct bitVector* input, int selector, int numWays) {
  struct bitVector** vectorOfVectors = malloc(numWays*sizeof(struct bitVector*));
  int vectorLength = input->length;
  unsigned long long zero = 0ULL;
  for(int i = 0; i < numWays; i++) {
    if(i == selector) {
      vectorOfVectors[i] = vector_copy(input);
    } else {
      vectorOfVectors[i] = init_vector_filled(zero, vectorLength);
    }
  }
  return vectorOfVectors;
}

struct bitVector* mux(struct bitVector** inputs, int selector) {
  return vector_copy(inputs[selector]);
}


#endif
