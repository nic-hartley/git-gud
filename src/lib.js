mergeInto(LibraryManager.library, {
  draw_commit_circle: function(x, y, color, isHead) {

    if (!isHead) {
      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2 * Math.PI);
      ctx.strokeStyle = "black";
      ctx.lineWidth = 2;
      ctx.stroke();
      ctx.fillStyle = UTF8ToString(color, 8);
      ctx.fill();
    }

    // Head commit have an additonal ring around them
    else {
      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS*0.75, 0, 2*Math.PI);
      ctx.fillStyle = UTF8ToString(color, 8);
      ctx.fill();

      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2*Math.PI);
      ctx.stokeStyle = "black";
      ctx.lineWidth = 3;
      ctx.stroke();
    }
  },
  
  connect_circles: function(topX, topY, botX, botY) {
    ctx.beginPath();
    // move to middle bottom of first circle
    ctx.moveTo(centerX(topX), centerY(topY) + CIRCLE_RADIUS);
    // do a pretty arc to the top of the last circle
    ctx.bezierCurveTo(
      centerX(topX), centerY(botY) - CIRCLE_RADIUS,
      centerX(botX), centerY(topY) + CIRCLE_RADIUS + VERT_MARGIN,
      centerX(botX), centerY(botY) - CIRCLE_RADIUS
    );
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 2;
    ctx.stroke();
  },

  set_relative_to: function(x, y) {
    // ctx.translate(centerX(x), centerY(y));
  },

  main_done: function() {
    Module._draw();
  },

  print: function(what) {
    console.log(UTF8ToString(what));
  },
});
