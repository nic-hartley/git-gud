#include "emscripten.h"

#include "git-gud.hpp"

extern "C" {
  extern void print(const char* message);
  extern void main_done();
  extern void set_relative_to(int x, int y);
  extern void draw_commit_circle(int x, int y, const char* color, bool isHead);
  extern void connect_circles(int tx, int ty, int bx, int by);
}

git_gud::GitTree tree;

int main() {
  main_done();
}

extern "C" {
  EMSCRIPTEN_KEEPALIVE
  void draw() {
    auto head = tree.getHead();
    set_relative_to(head->getBranch(), head->getID());
    for (auto commit : tree.getAllCommits()) {
      draw_commit_circle(commit->getBranch(), commit->getID(),
        "#85c1e9", tree.isHead(commit->getID())
      );
      for (auto parent : commit->getParents()) {
        connect_circles(
          parent->getBranch(), parent->getID(),
          commit->getBranch(), commit->getID()
        );
      }
    }
  }

  EMSCRIPTEN_KEEPALIVE
  void checkout_commit(int id) {
    tree.checkoutCommit(id);
  }

  EMSCRIPTEN_KEEPALIVE
  void checkout_branch(int id) {
    tree.checkout(id);
  }

  EMSCRIPTEN_KEEPALIVE
  void commit() {
    tree.addCommit();
  }
}
