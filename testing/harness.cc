#include "test.h"

int main() {
  ull seed = 42;
  if (test(seed)) {
    return 0;
  }
  return 1;
}
