const game = {
  gl: {},
  canvases: {},
  uiContainer: null,
  ready: false
};

function windowLoop() {
  if (!game.ready)
    return;
  
  _CallUpdate();
  _CallDraw();
}

window.addEventListener('resize', () => {
  if (!game.ready)
    return;

  game.canvas.width = window.innerWidth;
  game.canvas.height = window.innerHeight;
});

window.addEventListener('load', () => {
  setInterval(windowLoop, 1000/60);
});