const CIRCLE_RADIUS = 15;
const HORIZ_MARGIN = CIRCLE_RADIUS / 2;
const VERT_MARGIN = CIRCLE_RADIUS / 4;
const COL_WIDTH = CIRCLE_RADIUS * 2 + HORIZ_MARGIN * 2;
const ROW_HEIGHT = CIRCLE_RADIUS * 2 + VERT_MARGIN * 2;

function centerX(x) { return x * COL_WIDTH + CIRCLE_RADIUS + HORIZ_MARGIN; }
function centerY(y) { return y * ROW_HEIGHT + CIRCLE_RADIUS + VERT_MARGIN; }

function commit() {
  console.log("would do a commit");
}

function branch(name) {
  console.log("would make new branch", name);
}

function merge(into) {
  console.log("would merge", from, "into", into);
}
function checkout(into){
    console.log("would checkout from", from, "into", into);
}
