#include "emscripten.h"

#include "git-gud.hpp"

extern "C" {
  extern void print(const char* message);
  extern void draw_commit_circle(int x, int y, const char* color);
  extern void connect_circles(int tx, int ty, int bx, int by);
}

int main() {
  print("starting main");

  print("main done");
}

extern "C" {
  EMSCRIPTEN_KEEPALIVE
  void draw() {
    print("starting draw");

    print("draw done");
  }
}
