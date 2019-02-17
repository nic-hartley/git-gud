const CIRCLE_RADIUS = 15;
const HORIZ_MARGIN = CIRCLE_RADIUS / 2;
const VERT_MARGIN = CIRCLE_RADIUS / 2;
const COL_WIDTH = CIRCLE_RADIUS * 2 + HORIZ_MARGIN * 2;
const ROW_HEIGHT = CIRCLE_RADIUS * 2 + VERT_MARGIN * 2;
const LINE_ARC_RADIUS = VERT_MARGIN/2;

function centerX(x) { return x * COL_WIDTH + CIRCLE_RADIUS + HORIZ_MARGIN; }
function centerY(y) { return y * ROW_HEIGHT + CIRCLE_RADIUS + VERT_MARGIN; }

function init() {
  Module._init();
  Module._draw();
}

function commit() {
  Module._commit();
  Module._draw();
}

function branch() {
  Module._branch();
  Module._draw();
}
<<<<<<< HEAD
=======

>>>>>>> 7c94fb5c97bc78a1f15654052693115d0eb92750
function merge(from) {
  if (from[0] === 'c') {
    throw new Error("Can only merge branches");
  } else if (from[0] !== 'b') {
    throw new Error("Specify a branch to merge");
  } else {
    Module._merge(parseInt(from.substr(1), 10));
  }
  Module._draw();
}

function checkout(branch) {
  if (branch[0] === 'b') {
    Module._checkout_branch(parseInt(branch.substr(1), 10));
  } else if (branch[0] == 'c') {
    Module._checkout_commit(parseInt(branch.substr(1), 10));
  } else {
    throw new Error("Specify a branch or commit to check out");
  }
  Module._draw();
}
