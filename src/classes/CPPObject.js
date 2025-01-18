const fs = require("fs");
const path = require("path");
const utils = require("../utils");
const child_process = require("child_process");
const os = require("os");

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

const outputLocation = buildConfig.outputPath || process.cwd() + "/objs";
const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/table-engine/src/engine/";

const local_dependency_search = /#include "([^"]*)"/g;

/**
 * A reference class to a compilable `.cpp` file.
 */
class CPPObject {
  /**
   * Default Constructor
   * @param {string} name name of the .cpp file to be compiled
   */
  constructor(name) {
    this.name = path.basename(name, path.extname(name));
    this.path = path.dirname(name);

    this.lastModification = null;
    this.lastBuild = null;

    // Will assume that this does not create an error since this file should exist.

    this.lastModification = fs.statSync(
      `${this.path}/${this.name}.cpp`,
    ).atimeMs;

    // Ok this one can create an error
    try {
      this.lastBuild = fs.statSync(`${outputLocation}/${this.name}.o`);
    } catch (e) {
      this.lastBuild = null;
    }
  }

  /**
   * Returns a boolean to determine if this file needs to be built
   */
  needsBuild() {
    return this.lastBuild == null || this.lastModification > this.lastBuild;
  }

  /**
   * Builds the file if it has not been built since it's last modification
   */
  build() {
    if (!this.needsBuild()) return;

    let execCmd = `${EMCC} -c "${this.path}/${this.name}.cpp" -o "${outputLocation}/${this.name}.o" -std=c++20 -I${includeDir}`;
    console.log(`compiling ${this.name}.cpp with em++`);
    child_process.execSync(execCmd, { cwd: process.cwd() });
  }

  /**
   * Returns an array of all the .cpp files required to build this file
   *
   * @warn This process assumes the file has a .hpp file along with the .cpp file. Please code as if you were programming with OOP
   * @returns {String[]} Array of cpp files that this one depends on
   */
  get dependencies() {
    let fileData = fs.readFileSync(`${this.path}/${this.name}.hpp`, "utf8");
    let dependencies = [];

    // Get all immediate header file dependencies
    [...fileData.matchAll(local_dependency_search)].forEach((element) => {
      let file = this.path + "/" + element[1].replace(".hpp", ".cpp");
      dependencies.push(path.normalize(file));
    });

    // Recursively return the rest of the tree of dependencies
    if (dependencies.length != 0) {
      dependencies.forEach((dep) => {
        let more = new CPPObject(dep).dependencies;
        dependencies = [...new Set(dependencies.concat(more))];
      });
    }

    return dependencies;
  }
}

module.exports = CPPObject;
