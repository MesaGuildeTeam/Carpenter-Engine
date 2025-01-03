const game = {
  gl: {},
  canvases: {},
  uiContainer: null,
  ready: false,

  soundManager: null,
  songQueue: [],
  soundElements: {},
  sounds: {}
};

// Window Management

window.addEventListener('resize', () => {
  if (!game.ready)
    return;

  game.canvas.width = window.innerWidth;
  game.canvas.height = window.innerHeight;
});

// Game Loop 
function windowLoop() {
  if (!game.ready)
    return;
  
  _CallUpdate();
  _CallDraw();
}

window.addEventListener('load', () => {
  game.soundManager = new AudioContext();
  
  setInterval(windowLoop, 1000/60);
});
