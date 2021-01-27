#include "gates.h"
#include "vectoredBits.h"
#include "muxDmux.h"
#include "adder.h"
#include "alu.h"
#include <stdio.h>
#include <stdbool.h>

void print_vector(struct bitVector* vector);
void test();

int main() {
  bool zx = false;
  bool zy = true;
  bool nx = false;
  bool ny = true;
  bool f = true;
  bool no = true;

  unsigned long long test1 = 45922;
  unsigned long long test2 = 298;
  struct bitVector* vector1 = init_vector_filled(test1, 16);
  // char* vector1String = stringify_vector(vector1);
  struct bitVector* vector2 = init_vector_filled(test2, 16);
  // char* vector2String = stringify_vector(vector2);
  //
  struct aluOutput* output = alu(vector1, vector2, zx, zy, nx, ny, f, no);
  print_vector(output->vector);
  print_vector(vector1);
  print_vector(vector2);
  // struct bitVector* vector3 = operate_vector(vector1, vector2, xor);
  // char* vector3String = stringify_vector(vector3);
  // printf("Vector 1: %s\nVector 2: %s\nVector 3: %s\n", vector1String, vector2String, vector3String);

  // int j = 0;
  // struct bitVector** vectors = malloc(8*sizeof(struct bitVector*));
  // for(unsigned long long i = 57; j < 8; i *= 3) {
  //   vectors[j] = init_vector_filled(i, 64);
  //   j++;
  // }
  //
  // for(int i = 0; i < 8; i++) {
  //   print_vector(mux(vectors, i));
  // }

  // struct bitVector* copy = vector_copy(vector1);
  // print_vector(copy);

  // struct bitVector* vectorSum = sum(vector1, vector2);
  // unsigned long long longSum = test1 + test2;
  // struct bitVector* hackVectorSum = init_vector_filled(longSum, 8);
  //
  // print_vector(vectorSum);
  // print_vector(hackVectorSum);
}

void print_vector(struct bitVector* vector) {
  printf("%s\n", stringify_vector(vector));
}
