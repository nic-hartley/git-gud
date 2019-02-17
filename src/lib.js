mergeInto(LibraryManager.library, {
  draw_commit_circle: function(x, y, color) {
    ctx.beginPath();
    ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2 * Math.PI);
    ctx.strokeStyle = "black";
    ctx.lineWidth = 1;
    ctx.stroke();
    ctx.fillStyle = UTF8ToString(color, 8);
    ctx.fill();
  },
  
  connect_circles: function(topX, topY, botX, botY) {
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
  },

  set_relative_to: function(x, y) {
    relativeToX = x;
    relativeToY = y;
  },

  main_done: function() {
    Module._draw();
  },

  print: function(what) {
    console.log(UTF8ToString(what));
  },
});
