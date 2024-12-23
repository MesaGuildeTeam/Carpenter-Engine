/** @namespace Build */

const child_process = require('child_process');
const fs = require('node:fs');
const path = require('path');
const os = require('os');

const utils = require('./utils');

var buildConfig;

try {
  buildConfig = require(process.cwd() + '/tableconf.json') 
} catch (exception) {
  buildConfig = {};
};

const EMCC = (process.platform == 'win32' ? os.homedir() + "\\.table-engine\\emsdk\\upstream\\emscripten\\em++.bat" : "~/.table-engine/emsdk/upstream/emscripten/em++");

const srcLocation = buildConfig.inputPath || process.cwd() + '/src';
const outputLocation = buildConfig.outputPath || process.cwd() + '/objs';
const FrameworkLibrary = buildConfig.frameworkPath != null ? buildConfig.frameworkPath : process.cwd() + '/node_modules/table-engine/objs';
const includeDir = buildConfig.includeDir != null ? buildConfig.includeDir : 'node_modules/table-engine/src/engine/';
const staticDir = buildConfig.static != null ? buildConfig.static : 'node_modules/table-engine/src/static/';

/**
 * Recursive function
 * 
 * Gets every file with the extension from a certain directory and its child folders and runs a callback on it
 */
function processFiles(folder, extension, callback) {
  fs.readdirSync(folder).forEach(file => {
    if (fs.statSync(path.join(folder, file)).isDirectory()) {
      processFiles(path.join(folder, file), ".cpp", callback);
    } else if (file.endsWith(extension)) {
      callback(file.split('.')[0], folder);
    }
  })
}

/**
 * Builds the c++ file specified into a .o file
 * @param {string} path The file name based on the buildconfig.json
 * 
 * @memberof Build
 */
function buildFile(path, folder) {
  let execCmd = `${EMCC} -c "${folder}/${path}.cpp" -o "${outputLocation}/${path}.o" -std=c++20 -I${includeDir}`
  console.log(execCmd);
  child_process.execSync(execCmd, {"cwd": process.cwd()});
}


const defaultBuildSteps = {
  runBuild: true,
  runLink: true,
  runPackage: true 
}

/**
 * Goes through the whole build process of the game and its engine
 * @memberof Build
 */
function buildGame(config = defaultBuildSteps) {
  console.log(process.cwd())
  // Build process
  if (config.runBuild)
    processFiles(srcLocation, ".cpp", (file, folder) => {
      buildFile(file, folder);
    });

  // Link process
  if (config.runLink) {
    let filesList = "";
    processFiles(outputLocation, ".o", (file, folder) => {
      filesList = filesList + `"${folder}/${file}.o" `;
    });
    if (FrameworkLibrary != "")
      processFiles(FrameworkLibrary, ".o", (file, folder) => {
        filesList = filesList + `"${folder}/${file}.o" `;
      });

    let exec = `${EMCC} ${filesList} -o ./build/engine.js -sEXPORTED_FUNCTIONS=_CallUpdate,_CallDraw -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --bind -sALLOW_MEMORY_GROWTH`;
    console.log(exec);
    child_process.execSync(exec);
  }

  // Package process
  if (config.runPackage)
    console.log(child_process.execSync(`cp -r ${staticDir}/* ./build/`));

  return process.exit(0);
}

function processArgs(argv) {
  if (argv.length == 0)
    return defaultBuildSteps;

  let buildSettings = {};
  argv.forEach(element => {
    switch (element) {
      case '-b':
        buildSettings.runBuild = true;
        break;
      case '-l':
        buildSettings.runLink = true;
        break;
      case '-p':
        buildSettings.runPackage = true;
        break;
      default:
        utils.throwError("This parameter does not exist");
    }
  });

  return buildSettings;
}

module.exports = {
  buildGame: buildGame,
  processArgs: processArgs
}