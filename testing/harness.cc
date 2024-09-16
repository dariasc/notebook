#include "harness.h"

// we don't want to test memory leaks
extern "C"
const char* __asan_default_options() { return "detect_leaks=0"; }

int main() {
  ull seed = 42;
  if (test(seed)) {
    return 0;
  }
  return 1;
}
