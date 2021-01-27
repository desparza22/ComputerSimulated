#ifndef ADDER_H
#define ADDER_H

#include <stdbool.h>
#include "vectoredBits.h"

struct sumAndCarry;

struct sumAndCarry {
  struct bitVector* sum;
  bool carry;
};

struct bitVector* sum(struct bitVector* inputA, struct bitVector* inputB);
struct sumAndCarry* sum_help(struct bitVector* inputA, struct bitVector* inputB, bool previousCarry);
struct sumAndCarry* init_sumAndCarry(struct bitVector* sum, bool carry);
struct bitVector* increment(struct bitVector* vector);

struct bitVector* sum(struct bitVector* inputA, struct bitVector* inputB) {
  if(inputA->length != inputB->length) {
    printf("not prepared to add vectors of unequal lengths %d and %d, returning null", inputA->length, inputB->length);
    return NULL;
  } else {
    struct sumAndCarry* solution = sum_help(inputA, inputB, false);
    return solution->sum;
  }
}

struct sumAndCarry* sum_help(struct bitVector* inputA, struct bitVector* inputB, bool previousCarry) {
  struct bitVector* finalResultOfAddition;
  bool carry;
  if(1 == inputA->length) {
    struct bitVector* baseOfAddition = operate_vector(inputA, inputB, xor);
    struct bitVector* representPreviousCarry = vector_single_bit(previousCarry);
    finalResultOfAddition = operate_vector(baseOfAddition, representPreviousCarry, xor);

    struct bitVector* baseOfCarry1 = operate_vector(inputA, inputB, and);
    struct bitVector* baseOfCarry2 = operate_vector(baseOfAddition, representPreviousCarry, and);
    struct bitVector* finalResultOfCarry = operate_vector(baseOfCarry1, baseOfCarry2, or);
    carry = finalResultOfCarry->value;
  } else {
    struct sumAndCarry* rightSide = sum_help(inputA->right, inputB->right, previousCarry);
    struct sumAndCarry* leftSide = sum_help(inputA->left, inputB->left, rightSide->carry);
    finalResultOfAddition = vector_merge(leftSide->sum, rightSide->sum);
    carry = leftSide->carry;
  }
  return init_sumAndCarry(finalResultOfAddition, carry);
}

struct sumAndCarry* init_sumAndCarry(struct bitVector* sum, bool carry) {
  struct sumAndCarry* instance = malloc(sizeof(struct sumAndCarry));
  instance->sum = sum;
  instance->carry = carry;
  return instance;
}

struct bitVector* increment(struct bitVector* vector) {
  struct bitVector* one = init_vector_filled(1ULL, vector->length);
  return sum(vector, one);
}

#endif
