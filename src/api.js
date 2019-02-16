let canvas = document.querySelector("canvas");
let ctx = canvas.getContext('2d');

let helloMem = wasm.malloc(256, 256);
wasm({
  path: "./git-gud.wasm",
  imports: { env: {
    memory: helloMem,
    print: s => console.log(helloMem.cstr(s)),
    draw_commit_circle,
    connect_circles,
  } }
}).then(main).catch(console.error);

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

function draw_commit_circle(x, y, color) {
  ctx.beginPath();
  ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2 * Math.PI);
  ctx.strokeStyle = "black";
  ctx.lineWidth = 1;
  ctx.stroke();
  ctx.fillStyle = helloMem.cstr(color);
  ctx.fill();
}

function connect_circles(topX, topY, botX, botY) {
  ctx.beginPath();
  // move to middle bottom of first circle
  ctx.moveTo(centerX(topX), centerY(topY) + CIRCLE_RADIUS);
  // draw a line a little bit down (halfway into the gap)
  ctx.lineTo(centerX(topX), centerY(topY) + CIRCLE_RADIUS + VERT_MARGIN);
  // draw a line across to line up with the bottom
  ctx.lineTo(centerX(botX), centerY(topY) + CIRCLE_RADIUS + VERT_MARGIN);
  // draw a line down to the top middle of that circle
  ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
  // and actually draw it onto the canvas
  ctx.strokeStyle = 'black';
  ctx.lineWidth = 2;
  ctx.stroke();
}

function main(cpp) {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  cpp.draw();
}

