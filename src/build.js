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
    ? os.homedir() + "\\.table-engine\\emsdk\\upstream\\emscripten\\em++.bat"
    : "~/.table-engine/emsdk/upstream/emscripten/em++";

const srcLocation = buildConfig.inputPath || process.cwd() + "/src";
const outputLocation = buildConfig.outputPath || process.cwd() + "/objs";
const FrameworkLibrary =
  buildConfig.frameworkPath != null
    ? buildConfig.frameworkPath
    : process.cwd() + "/node_modules/table-engine/objs";
const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/table-engine/src/engine/";
const staticDir =
  buildConfig.static != null
    ? buildConfig.static
    : "node_modules/table-engine/src/static/";

const defaultBuildSteps = {
  runBuild: true,
  runLink: true,
  runPackage: true,
  mainFile: "",
};

/**
 * Goes through the whole build process of the game and its engine:
 * 1. Starts with building each C++ file in the src folder through the `-c` flag
 * 2. Then links all the object files together through the `-l` flag
 * 3. Finally packages the game into a static webpage through the `-p` flag
 * 
 * If you wish to include a custom main file for testing, you can use the `-m` flag with the path to the file
 * 
 * @memberof Build
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
    if (FrameworkLibrary != "")
      utils.processFiles(FrameworkLibrary, ".o", (file, folder) => {
        filesList = filesList + `"${folder}/${file}.o" `;
      });

    let exec = `${EMCC} ${filesList} ${config.mainFile != "" && config.mainFile != null ? config.mainFile + " -I" + includeDir : ""} -o ./build/engine.js -std=c++20 -sEXPORTED_FUNCTIONS=_Engine_CallUpdate,_Engine_CallDraw -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --bind -sALLOW_MEMORY_GROWTH -sMAX_WEBGL_VERSION=2 -sASYNCIFY`;
    utils.execCommand(exec, "Linking Game");
  }

  // Package process
  if (config.runPackage) {
    console.log(child_process.execSync(`cp -r ${staticDir}/* ./build/`));
    console.log(child_process.execSync(`cp -r ./Assets ./build/`));
  }

  console.log("Build process finished successfully!");

  return process.exit(0);
}

module.exports = {
  buildGame: buildGame
}