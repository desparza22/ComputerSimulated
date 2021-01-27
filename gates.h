#ifndef GATES_H
#define GATES_H

#include <stdio.h>
#include <stdbool.h>

bool nand(bool inputA, bool inputB);
bool not(bool input);
bool not_wrap(bool inputA, bool inputB);
bool and(bool inputA, bool inputB);
bool or(bool inputA, bool inputB);
bool xor(bool inputA, bool inputB);
void printResult(bool boolean);

bool nand(bool inputA, bool inputB) {
  return !(inputA && inputB);
}

bool not(bool input) {
  return nand(input, input);
}

bool not_wrap(bool inputA, bool inputB) {
  return not(inputA);
}

bool and(bool inputA, bool inputB) {
  return not(nand(inputA, inputB));
}

bool or(bool inputA, bool inputB) {
  return nand(not(inputA), not(inputB));
}

bool xor(bool inputA, bool inputB) {
  return and(nand(inputA, inputB), or(inputA, inputB));
}

void printResult(bool boolean) {
  if(boolean) {
    printf("true\n");
  } else {
    printf("false\n");
  }
}

#endif
