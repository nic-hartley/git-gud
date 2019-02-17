const CIRCLE_RADIUS = 15;
const HORIZ_MARGIN = CIRCLE_RADIUS / 2;
const VERT_MARGIN = CIRCLE_RADIUS / 4;
const COL_WIDTH = CIRCLE_RADIUS * 2 + HORIZ_MARGIN * 2;
const ROW_HEIGHT = CIRCLE_RADIUS * 2 + VERT_MARGIN * 2;

console.log("CIRCLE_RADIUS", CIRCLE_RADIUS);
console.log("HORIZ_MARGIN", HORIZ_MARGIN);
console.log("VERT_MARGIN", VERT_MARGIN);
console.log("COL_WIDTH", COL_WIDTH);
console.log("ROW_HEIGHT", ROW_HEIGHT);

function centerX(x) { return x * COL_WIDTH + CIRCLE_RADIUS + HORIZ_MARGIN; }
function centerY(y) { return y * ROW_HEIGHT + CIRCLE_RADIUS + VERT_MARGIN; }

Module.onRuntimeInitialized = () => {
  Module._draw();
}

function commit() {
  console.log("would do a commit");
}

function branch(name) {
  console.log("would make new branch", name);
}

function merge(into, from) {
  console.log("would merge", from, "into", into);
}
function checkout(into, from){
    console.log("would checkout from", from, "into", into);
}
