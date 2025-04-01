/** @namespace Client */

const game = {
  // Graphics & UI
  gl: {},
  canvases: {},
  uiContainer: null,
  ready: false,

  // Audio

  musicManager: null,
  playerReady: false,
  songQueue: [],
  sounds: {},
  musicNodes: {},
  musicVolume: null,

  // Classes

  Audio: null,
};

// Audio System

/**
 * A callback used to run the music queue when the window has been clicked anywhere once.
 *
 * Due to autoplay by default being disabled on browsers, the autoplay must occur when the screen has been clicked once. This method is called to do that when the screen is clicked.
 *
 * @namespace Client
 */
function PrepareAudioModule() {
  if (game.playerReady) {
    game.songQueue[0].play();
    game.musicManager.resume();
    window.removeEventListener("click", PrepareAudioModule);
  }
}

/**
 * A sound class container implemented in JavaScript.
 *
 * This class is the JavaScript representation of the engine's Sound class.
 * These are created via `Engine::Audio::Audio` (and its subclasses) to be manipulated easier.
 */
game.Audio = class {
  constructor(filename) {
    this.filename = filename;
    this.element = new Audio(filename);
    this.source = game.musicManager.createMediaElementSource(this.element);
    this.type = null;
    this.loop = false;

    // These are values to be assigned to the buffers when they are created
    // They are assigned in the constructor for easy access, but they are only used in sounds
    // the 1 is the base value of the gain
    // the 0 is the base value of the panning
    this.buffers = [1, 0];

    this.element.addEventListener("ended", () => {
      if (!this.loop) game.songQueue.shift();

      if (game.songQueue.length > 0) game.songQueue[0].play();
    });
  }

  /**
   * Takes the sound and prepares it to be played in the song queue
   */
  makeSong() {
    this.type = "song";
    this.source.connect(game.musicVolume);
  }

  makeSound() {
    this.type = "sound";
  }

  /**
   * Sets the gain and panning of the sound for the next playthrough
   *
   * @param {float} gain a value to multiply the sound by
   * @param {float} panning a value between -1 and 1 to pan the sound
   * @warn This is only useful if this is being used as a sound
   */
  setBuffers(gain = 1, panning = 0) {
    this.buffers = [gain, panning];
  }

  /**
   * Plays the audio file as defined by the type.
   *
   * If this is a song, it will play the first song in the queue
   */
  play() {
    if (this.type == "sound") {
      let soundClone = this.element.cloneNode(true);
      let tempGain = game.musicManager.createGain();
      tempGain.gain.value = this.buffers[0];

      let tempPanner = new StereoPannerNode(game.musicManager, {
        pan: this.buffers[1],
      });

      game.musicManager
        .createMediaElementSource(soundClone)
        .connect(tempGain)
        .connect(tempPanner)
        .connect(game.musicManager.destination);

      soundClone.play();

      return;
    }

    if (this.type == "song") {
      if (!game.songQueue.includes(this)) game.songQueue.push(this);

      if (game.musicManager.state == "suspended") {
        game.songQueue[0].element.play().catch((e) => {
          console.warn(
            "WARNING: Engine can not play audio yet. Engine will tell music queue ",
          );
          game.playerReady = true;
          window.addEventListener("click", PrepareAudioModule);
        });
        return;
      }

      game.songQueue[0].element.play();
      return;
    }

    throw new Error(
      `ERROR: Although this should have been done already, this needs to be prepared as a Song or a Sound before use`,
    );
  }

  /**
   * Pauses the audio file
   *
   * @warn This is only useful if this is a song
   */
  pause() {
    this.element.pause();
  }

  isPlaying() {
    if (this.type == "song") return this.element.paused == false;

    return false;
  }

  setLoop(mode) {
    this.loop = mode;
  }
};

window.addEventListener("resize", () => {
  if (!game.ready) return;

  game.canvases["canvas"].width = window.innerWidth;
  game.canvases["canvas"].height = window.innerHeight;
  game.gl["canvas"].viewport(0, 0, window.innerWidth, window.innerHeight);
});

// Game Loop

var lastTime = new Date().getTime();

function update() {
  var now = new Date().getTime();
  _Engine_CallUpdate((now - lastTime) / 1000);
  lastTime = now;
};

function draw() {_Engine_CallDraw()};

function windowLoop() {
  if (!game.ready) return setTimeout(windowLoop, 100);

  update();
  draw();

  setTimeout(windowLoop, 1000 / 60);
}

window.addEventListener("load", () => {
  game.musicManager = new AudioContext({ autoplay: true });
  game.musicVolume = game.musicManager.createGain();
  game.musicVolume.gain.value = 1;
  game.musicVolume.connect(game.musicManager.destination);

  windowLoop();
});
