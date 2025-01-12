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
    utils.processFiles(srcLocation, ".cpp", (file, folder) => {
      buildFile(file, folder);
    });

  // Link process
  if (config.runLink) {
    let filesList = "";
    utils.processFiles(outputLocation, ".o", (file, folder) => {
      filesList = filesList + `"${folder}/${file}.o" `;
    });
    if (FrameworkLibrary != "")
      utils.processFiles(FrameworkLibrary, ".o", (file, folder) => {
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

module.exports = {
  buildGame: buildGame,
}