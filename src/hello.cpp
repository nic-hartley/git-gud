#include "emscripten.h"

extern "C" {
  extern void print(int num, int val);

  EMSCRIPTEN_KEEPALIVE
  void print_val(int num) {
    print(1, num);
    print(2, 100);
    print(3, num * 2);
  }
}
