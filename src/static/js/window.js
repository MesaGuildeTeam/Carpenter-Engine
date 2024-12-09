const game = {
  gl: null,
  canvas: null,
  uiContainer: null,
  ready: false
};

function windowLoop() {
  if (game.ready == true) {
      _CallUpdate();
      _CallDraw();
  }
}

window.addEventListener('resize', function() {
  game.canvas.width = window.innerWidth;
  game.canvas.height = window.innerHeight;
});

window.addEventListener('load', function() {
  setInterval(windowLoop, 1000/60);
});