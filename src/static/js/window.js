/** @namespace Client */

const game = {
  gl: {},
  canvases: {},
  uiContainer: null,
  ready: false,

  musicManager: null,
  playerReady: false,
  songQueue: [],
  sounds: {},
  musicNodes: {},

  // Classes

  Audio: null,
};

// Audio System

/**
 * A callback used to run the music queue when the window has been clicked anywhere once.
 * 
 * Due to autoplay by default being disabled on browsers, the autoplay must occur when the screen has been clicked once. This method is called to do that when the screen is clicked.
 */
function PrepareAudioModule() {
  if (game.playerReady) {
    game.songQueue[0].play();
    game.musicManager.resume();
    window.removeEventListener('click', PrepareAudioModule);
  }
}

/**
 * A sound class container implemented in JavaScript.
 * 
 * This class is the JavaScript representation of the engine's Sound class.
 * These are created via `Engine::Audio::Audio` (and its subclasses) to be manipulated easier.
 * 
 * @namespace Client
 */
game.Audio = class {
  constructor(filename) {
    this.filename = filename;
    this.element = new Audio(filename);
    this.source = game.musicManager.createMediaElementSource(this.element);
    this.type = null;

    this.element.addEventListener('ended', () => {
      game.songQueue.shift();

      if (this.musicManager.songQueue.length > 0)
        this.songQueue[0].Play();
    });
  }

  /**
   * Takes the sound and prepares it to be played in the song queue
   */
  makeSong() {
    this.type = 'song';
    this.source.connect(game.musicManager.destination);
  }

  /**
   * Plays the audio file as defined by the type.
   * 
   * If this is a song, it will play the first song in the queue
   */
  play() {
    if (this.type == 'song') {
      if (!game.songQueue.includes(this))
        game.songQueue.push(this);
      
      if (game.musicManager.state == 'suspended') {
        game.songQueue[0].element.play().catch(e => {
          console.warn("WARNING: Engine can not play audio yet. Engine will tell music queue ");
          game.playerReady = true;
          window.addEventListener('click', PrepareAudioModule);
        });
        return;
      }     

      game.songQueue[0].element.play();
      return;
    }

    throw new Error(`ERROR: Although this should have been done already, this needs to be prepared as a Song or a Sound before use`);
  }

  /**
   * Pauses the audio file
   */
  pause() {
    this.element.pause();
  }

  isPlaying() {
    if (this.type == 'song')
      return this.element.currentTime > 0 && this.element.currentTime < this.element.duration;

    return false;
  }
}

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
  game.musicManager = new AudioContext({autoplay: true});
  
  setInterval(windowLoop, 1000/60);
});
