#include "emscripten.h"

#include "git-gud.hpp"

extern "C" {
  extern void print(const char* message);
  extern void main_done();
  extern void set_relative_to(int x, int y);
  extern void draw_commit_circle(int x, int y, const char* color);
  extern void connect_circles(int tx, int ty, int bx, int by);
}

git_gud::GitTree tree;

int main() {
  print("starting main");
  tree.addCommit();
  tree.addCommit();
  auto newBranch = tree.addCommitNewBranch();
  tree.checkout(0);
  tree.addCommit();
  tree.checkout(newBranch->getBranch());
  tree.addCommit();
  tree.checkout(0);
  tree.merge(1);
  tree.addCommit();
  tree.checkout(1);
  tree.addCommitNewBranch();
  tree.checkoutCommit(newBranch->getID());
  tree.addCommitNewBranch();
  tree.checkout(1);
  tree.merge(3);
  tree.checkout(0);
  tree.merge(2);
  print("main done");
  main_done();
}

extern "C" {
  EMSCRIPTEN_KEEPALIVE
  void draw() {
    print("starting draw");
    auto head = tree.getHead();
    set_relative_to(head->getBranch(), head->getID());
    for (auto commit : tree.getAllCommits()) {
      print("Drawing commit");
      draw_commit_circle(commit->getBranch(), commit->getID(),
        tree.isHead(commit->getID()) ? "green" : "red"
      );
      for (auto parent : commit->getParents()) {
        connect_circles(
          parent->getBranch(), parent->getID(),
          commit->getBranch(), commit->getID()
        );
      }
    }
    print("draw done");
  }
}
