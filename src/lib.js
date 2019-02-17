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

    ctx.strokeStyle = 'black';
    ctx.lineWidth = 2;

    // If botX == botY, it's a straight line
    if (botX == topX) {
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
      ctx.stroke();
    }

    // If botX is greater than topX, it's a branch, and the
    // branch line should be near the top
    else if (botX > topX) {
      ctx.lineTo(centerX(topX), centerY(topY) + CIRCLE_RADIUS + (VERT_MARGIN/2));
      ctx.stroke();
      ctx.lineTo(centerX(botX), centerY(topY) + CIRCLE_RADIUS + (VERT_MARGIN/2));
      ctx.stroke();
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS );
      ctx.stroke();
    }

    // If botX is less than topX, it's a merge, and the line should
    // be near the bottom
    else {
      ctx.lineTo(centerX(topX), centerY(botY) - CIRCLE_RADIUS - (VERT_MARGIN/2));
      ctx.stroke();
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS - (VERT_MARGIN/2));
      ctx.stroke();
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
      ctx.stroke();
    }
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
