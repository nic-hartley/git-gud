mergeInto(LibraryManager.library, {
  draw_commit_circle: function(ID, x, y, isHead) {
    if (isHead) {
      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS*0.75, 0, 2*Math.PI);
      ctx.fillStyle = "#00FF00";
      ctx.fill();

      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2*Math.PI);
      ctx.stokeStyle = "black";
      ctx.lineWidth = 3;
      ctx.stroke();
    } else {
      ctx.beginPath();
      ctx.arc(centerX(x), centerY(y), CIRCLE_RADIUS, 0, 2 * Math.PI);
      ctx.strokeStyle = "black";
      ctx.lineWidth = 2;
      ctx.stroke();
      ctx.fillStyle = "#85c1e9";
      ctx.fill();
    }

    // Draw the commit ID in the center
    ctx.font = "10px Arial";
    ctx.fillStyle = "black"
    var text = "c" + ID.toString();
    var leftOffset = ctx.measureText(text).width / 2;
    ctx.fillText(text, centerX(x) - leftOffset, centerY(y));
  },
  
  connect_circles: function(topX, topY, botX, botY, isMerge) {
    ctx.beginPath();
    // move to middle bottom of first circle
    ctx.moveTo(centerX(topX), centerY(topY) + CIRCLE_RADIUS);

    // If botX == botY, it's a straight line
    if (botX == topX) {
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
    } else if (isMerge && botX > topX) {
      ctx.lineTo(centerX(topX), centerY(botY) - CIRCLE_RADIUS - VERT_MARGIN - LINE_ARC_RADIUS);
      ctx.arc(centerX(topX) + LINE_ARC_RADIUS,
              centerY(botY) - CIRCLE_RADIUS - VERT_MARGIN - LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              Math.PI, Math.PI/2, true);
      ctx.lineTo(centerX(botX) - LINE_ARC_RADIUS,
                 centerY(botY) - CIRCLE_RADIUS - (VERT_MARGIN));
      ctx.arc(centerX(botX) - LINE_ARC_RADIUS,
              centerY(botY) - CIRCLE_RADIUS - LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              1.5*Math.PI,
              0);
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
    } else if (isMerge && botX < topX) {
      ctx.lineTo(centerX(topX), centerY(botY) - CIRCLE_RADIUS - VERT_MARGIN - LINE_ARC_RADIUS);
      ctx.arc(centerX(topX) - LINE_ARC_RADIUS,
              centerY(botY) - CIRCLE_RADIUS - VERT_MARGIN - LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              0, Math.PI / 2);
      ctx.lineTo(centerX(botX) + LINE_ARC_RADIUS,
                 centerY(botY) - CIRCLE_RADIUS - (VERT_MARGIN));
      ctx.arc(centerX(botX) + LINE_ARC_RADIUS,
              centerY(botY) - CIRCLE_RADIUS - LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              1.5*Math.PI, Math.PI, true);
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
    } else if (botX > topX) {
      ctx.lineTo(centerX(topX), centerX(topY) + CIRCLE_RADIUS + LINE_ARC_RADIUS);
      ctx.arc(centerX(topX) + LINE_ARC_RADIUS,
              centerY(topY) + CIRCLE_RADIUS + LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              Math.PI, Math.PI / 2, true); // counterclockwise
      ctx.lineTo(centerX(botX) - LINE_ARC_RADIUS, centerY(topY) + CIRCLE_RADIUS + (VERT_MARGIN));
      ctx.arc(centerX(botX)-LINE_ARC_RADIUS,
              centerY(topY) + CIRCLE_RADIUS + VERT_MARGIN + LINE_ARC_RADIUS,
              LINE_ARC_RADIUS,
              1.5 * Math.PI, 0);
      ctx.lineTo(centerX(botX), centerY(botY) - CIRCLE_RADIUS);
    }

    ctx.strokeStyle = 'black';
    ctx.lineWidth = 2;
    ctx.stroke();
  },

  draw_columns: function(numColumns, current) {
    ctx.beginPath();
    ctx.strokeStyle = "gray";
    ctx.lineWidth = 1;

    ctx.fillStyle = "#AAAAAAAA";
    ctx.fillRect(COL_WIDTH * current, 0, COL_WIDTH, canvas.height);

    for (var i = 0; i < numColumns; i++) {
      var rightSide = COL_WIDTH * (i+1);
      ctx.moveTo(rightSide, 0);
      ctx.lineTo(rightSide, canvas.height);

      // Draw the branch ID in the center
      ctx.font = "10px Arial";
      ctx.fillStyle = "black";
      var text = "b" + i.toString();
      var leftOffset = ctx.measureText(text).width / 2;
      ctx.fillText(text, (COL_WIDTH * i) + COL_WIDTH/2 - leftOffset,10);
    }
    ctx.stroke();
  },

  start_draw: function(x, y) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.save();
  },

  translate: function(x, y) {
    ctx.translate(x, y);
  },

  end_draw: function() {
    ctx.restore();
  },

  main_done: function() {
    Module._draw();
  },

  print: function(what) {
    console.log(UTF8ToString(what));
  },
});
