#include "emscripten.h"

extern "C" {
  extern void print(const char* message);
  extern void draw_commit_circle(int x, int y, const char* color);
  extern void connect_circles(int tx, int ty, int bx, int by);

  EMSCRIPTEN_KEEPALIVE
  void draw() {
    print("before");
    draw_commit_circle(1, 4, "blue");
    draw_commit_circle(2, 2, "red");
    draw_commit_circle(3, 3, "green");
    draw_commit_circle(3, 5, "magenta");
    connect_circles(2, 2, 3, 3);
    connect_circles(2, 2, 1, 4);
    connect_circles(3, 3, 3, 5);

    print("after");
  }
}
