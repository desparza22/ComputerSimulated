#ifndef VECTOREDBITS_H
#define VECTOREDBITS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct bitVector;

struct bitVector{
  bool value;
  int length;
  struct bitVector *left;
  struct bitVector *right;
};

struct bitVector* init_vector_filled(unsigned long long number, int bitCapacity);
struct bitVector* init_vector_empty(int bitCapacity);
struct bitVector* vector_merge(struct bitVector* left, struct bitVector* right);
struct bitVector *operate_vector(struct bitVector *inputA, struct bitVector *inputB, bool (*f)(bool, bool));
struct bitVector *operate_vector_help(struct bitVector *inputA, struct bitVector *inputB, bool (*f)(bool, bool));
unsigned long long left_n_bits(unsigned long long number, int numBits);
unsigned long long right_n_bits(unsigned long long number, int numBits);
unsigned long long ones_mask(int numOnes);
char *stringify_long(unsigned long long number);
char *stringify_vector(struct bitVector* vector);
void stringify_vector_help(struct bitVector* vector, int start, char* string);
struct bitVector* vector_copy(struct bitVector* original);
struct bitVector* vector_single_bit(bool value);

struct bitVector* init_vector_filled(unsigned long long number, int bitCapacity) {
  struct bitVector *vector;
  vector = (struct bitVector*) malloc(sizeof(struct bitVector));
  vector->length = bitCapacity;
  if(bitCapacity == 1) {
    vector->left = NULL;
    vector->right = NULL;
    vector->value = number == 1;
  } else {
    vector->left = init_vector_filled(left_n_bits(number, bitCapacity/2), bitCapacity/2);
    vector->right = init_vector_filled(right_n_bits(number, bitCapacity/2), bitCapacity/2);
  }
  return vector;
}

struct bitVector* init_vector_empty(int bitCapacity) {
  struct bitVector *vector = (struct bitVector*) malloc(sizeof(struct bitVector));
  vector->length = bitCapacity;
  return vector;
}

struct bitVector* vector_merge(struct bitVector *left, struct bitVector *right) {
  if(left->length != right->length) {
    printf("not prepared to merge vectors of different lengths %d and %d, returning null\n", left->length, right->length);
    return NULL;
  } else {
    struct bitVector* merging = init_vector_empty(left->length+right->length);
    merging->left = left;
    merging->right = right;
    return merging;
  }
}

struct bitVector* vector_copy(struct bitVector* original) {
  unsigned long long onesMask = ones_mask(original->length);
  struct bitVector* selector = init_vector_filled(onesMask, original->length);
  return operate_vector(selector, original, and);
}

struct bitVector* vector_single_bit(bool value) {
  unsigned long long numberValue = value? 1ULL: 0ULL;
  struct bitVector* singleBit = init_vector_filled(numberValue, 1);
  return singleBit;
}

struct bitVector* operate_vector(struct bitVector *inputA, struct bitVector *inputB, bool (*f)(bool, bool)) {
  if(inputA->length != inputB->length) {
    printf("invalid input vectors passed of lengths %d and %d\n", inputA->length, inputB->length);
    return NULL;
  } else {
    return operate_vector_help(inputA, inputB, f);
  }
}

struct bitVector* operate_vector_help(struct bitVector *inputA, struct bitVector *inputB, bool (*f)(bool, bool)) {
  struct bitVector *toReturn = init_vector_empty(inputA->length);
  if(inputA->length == 1) {
    toReturn->value = (*f)(inputA->value, inputB->value);
    toReturn->left = NULL;
    toReturn->right = NULL;
  } else {
    toReturn->left = operate_vector_help(inputA->left, inputB->left, f);
    toReturn->right = operate_vector_help(inputA->right, inputB->right, f);
  }
  return toReturn;
}

unsigned long long left_n_bits(unsigned long long number, int numBits) {
  unsigned long long allones_mask = ones_mask(numBits);
  allones_mask = allones_mask << numBits;
  return (number & allones_mask) >> numBits;
}

unsigned long long right_n_bits(unsigned long long number, int numBits) {
  unsigned long long allones_mask = ones_mask(numBits);
  return number & allones_mask;
}

unsigned long long ones_mask(int numOnes) {
  if(numOnes == 64) {
    return -1;
  }
  return (1ULL<<numOnes) - 1;
}

char* stringify_long(unsigned long long number) {
  char *string = (char*) calloc(1, sizeof(char)*65);
  unsigned long long mask = 1ULL;
  for(int i = 63; i >= 0; i--) {
    string[63-i] = (char) ((((mask<<i) & number) >> i) + 48);
  }
  string[64] = '\0';
  return string;
}

char *stringify_vector(struct bitVector* vector) {
  char *string = malloc(vector->length*sizeof(char));
  stringify_vector_help(vector, 0, string);
  return string;
}

void stringify_vector_help(struct bitVector* vector, int start, char* string) {
  if(1 == vector->length) {
    if(vector->value) {
      string[start] = '1';
    } else {
      string[start] = '0';
    }
  } else {
    stringify_vector_help(vector->left, start, string);
    stringify_vector_help(vector->right, start + vector->length/2, string);
  }
}

#endif
