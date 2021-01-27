#ifndef ALU_H
#define ALU_H

#include <stdlib.h>
#include "vectoredBits.h"
#include "gates.h"
#include "adder.h"

struct aluOutput;

struct aluOutput {
  struct bitVector* vector;
  bool zero;
  bool negative;
};

struct aluOutput* alu(struct bitVector* x, struct bitVector* y, bool zx, bool zy, bool nx, bool ny, bool f, bool no);
struct bitVector* zero_vector(struct bitVector* original);
bool vector_is_zero(struct bitVector* vector);
bool vector_is_negative(struct bitVector* vector);
bool vector_leftmost_bit_set(struct bitVector* vector);
struct aluOutput* init_aluOutput(struct bitVector* vector, bool zero, bool negative);

struct aluOutput* alu(struct bitVector* x, struct bitVector* y, bool zx, bool zy, bool nx, bool ny, bool f, bool no) {
  if(zx) {
    x = zero_vector(x);
  }
  if(zy) {
    y = zero_vector(y);
  }
  if(nx) {
    x = operate_vector(x, x, not_wrap);
  }
  if(ny) {
    y = operate_vector(y, y, not_wrap);
  }
  struct bitVector* output;
  if(f) {
    output = sum(x, y);
  } else {
    output = operate_vector(x, y, and);
  }
  if(no) {
    output = operate_vector(output, output, not_wrap);
  }
  return init_aluOutput(output, vector_is_zero(output), vector_is_negative(output));
}

struct bitVector* zero_vector(struct bitVector* original) {
  return operate_vector(original, original, xor);
}

bool vector_is_zero(struct bitVector* vector) {
  if(1 == vector->length) {
    return !(vector->value);
  } else {
    return vector_is_zero(vector->left) && vector_is_zero(vector->right);
  }
}

bool vector_is_negative(struct bitVector* vector) {
  return vector_leftmost_bit_set(vector);
}

bool vector_leftmost_bit_set(struct bitVector* vector) {
  if(1 == vector->length) {
    return vector->value;
  } else {
    return vector_leftmost_bit_set(vector->left);
  }
}

struct aluOutput* init_aluOutput(struct bitVector* vector, bool zero, bool negative) {
  struct aluOutput* output = malloc(sizeof(struct aluOutput));
  output->vector = vector;
  output->zero = zero;
  output->negative = negative;
  return output;
}

#endif
