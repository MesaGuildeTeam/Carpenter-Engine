/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/** @namespace Build */

const child_process = require("child_process");
const fs = require("node:fs");
const path = require("path");
const os = require("os");

const utils = require("./utils");
const CPPObject = require("./classes/CPPObject");

var buildConfig;

try {
  buildConfig = require(process.cwd() + "/tableconf.json");
} catch (exception) {
  buildConfig = {};
}

const EMCC =
  process.platform == "win32"
    ? os.homedir() + "\\.mesaguilde\\emsdk\\upstream\\emscripten\\em++.bat"
    : "~/.mesaguilde/emsdk/upstream/emscripten/em++";

const EMAR =
  process.platform == "win32"
    ? os.homedir() + "\\.mesaguilde\\emsdk\\upstream\\emscripten\\emar.bat"
    : "~/.mesaguilde/emsdk/upstream/emscripten/emar";

const srcLocation = buildConfig.inputPath || process.cwd() + "/src";
const outputLocation = buildConfig.outputPath || process.cwd() + "/objs";

const FrameworkLibrary =
  buildConfig.frameworkPath != null
    ? buildConfig.frameworkPath
    : "./node_modules/@mesaguilde/carpenter-engine/build/carpenterengine.a";

const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/@mesaguilde/carpenter-engine/src/engine/";

const staticDir =
  buildConfig.static != null
    ? buildConfig.static
    : "node_modules/@mesaguilde/carpenter-engine/src/static/";

const defaultBuildSteps = {
  runBuild: true,
  runLink: true,
  runPackage: false,
  mainFile: "",
  debug: false,
  libMode: false,
};

/**
 * Goes through the whole build process of the game and its engine:
 * 1. Starts with building each C++ file in the src folder through the `-c` flag
 * 2. Then links all the object files together through the `-l` flag
 * 3. Finally packages the game into a static webpage through the `-p` flag
 *
 * If you wish to include a custom main file for testing, you can use the `-m`
 * flag with the path to the file.
 *
 * @param {Object} config - The configuration object; see defaultBuildSteps
 * @returns {process} The exit code
 * @memberof Build
 * @author Roberto Selles
 */
function buildGame(config = defaultBuildSteps) {
  // Build process
  if (config.runBuild)
    utils.processFiles(srcLocation, ".cpp", (file, folder) => {
      new CPPObject(`${folder}/${file}.cpp}`).build();
    });

  // Link process
  if (config.runLink) {
    let filesList = "";
    utils.processFiles(outputLocation, ".o", (file, folder) => {
      filesList = filesList + `"${folder}/${file}.o" `;
    });

    let debugMethods = config.debug == true ? "-g -gsource-map" : "";

    let exec = `${EMCC} ${filesList} ${config.mainFile != "" && config.mainFile != null ? config.mainFile + " -I" + includeDir : ""} ${FrameworkLibrary} -o ./build/engine.js -std=c++20 -sEXPORTED_FUNCTIONS=_Engine_CallUpdate,_Engine_CallDraw -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --bind -sALLOW_MEMORY_GROWTH -sMAX_WEBGL_VERSION=2 -sASYNCIFY -sASYNCIFY_STACK_SIZE=4096 ${debugMethods}`;

    if (config.libMode == true)
      exec = `${EMAR} rcs ./build/carpenterengine.a ${filesList}`;

    utils.execCommand(exec, "Linking Game");
  }

  // Package process
  if (config.runPackage)
    console.log(child_process.execSync(`cp -r ${staticDir}/* ./build/`));

  console.log("Build process finished successfully!");

  return process.exit(0);
}

module.exports = {
  buildGame: buildGame,
};
