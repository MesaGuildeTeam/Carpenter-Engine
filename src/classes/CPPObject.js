/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

const fs = require("fs");
const path = require("path");
const utils = require("../utils");
const os = require("os");

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

const outputLocation = buildConfig.outputPath || "./objs";
const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/@mesaguilde/carpenter-engine/src/engine/";

const local_dependency_search = /#include "([^"]*)\"/g;

var visitedArray = [];

/**
 * @brief A reference class to a compilable `.cpp` file.
 * Allows the program to determine if a file needs to be built or not and check
 * for its dependencies recursively to determine what it needs to link with.
 * 
 * @author Roberto Selles
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

    if (fs.existsSync(`${this.path}/${this.name}.cpp`)) {
      this.lastModification = fs.statSync(
        `${this.path}/${this.name}.cpp`,
      ).atimeMs;
    }

    // Ok this one can create an error
    try {
      this.lastBuild = fs.statSync(`${outputLocation}/${this.name}.o`).atimeMs;
    } catch (e) {
      this.lastBuild = null;
    }
  }

  /**
   * A method that returns if this file needs to be built
   * @returns {boolean}
   */
  needsBuild() {
    if (!fs.existsSync(`${this.path}/${this.name}.cpp`)) return false;
    return this.lastBuild == null || this.lastModification > this.lastBuild;
  }

  /**
   * Builds the file if it has not been built since it's last modification
   */
  build() {
    if (!this.needsBuild()) return;

    let execCmd = `${EMCC} -c "${this.path}/${this.name}.cpp" -o "${outputLocation}/${this.name}.o" -std=c++20 -I${includeDir} -Iinclude/`;
    utils.execCommand(execCmd, `Compiling ${this.name}.cpp`);
  }

  /**
   * Returns an array of all the .cpp files required to build this file
   *
   * @warn This process assumes the file has a .hpp file along with the .cpp file. Please code as if you were programming with OOP
   * @returns {String[]} Array of cpp files that this one depends on
   */
  getDependencies(root = true) {
    if (root == true) visitedArray = [];
    if (visitedArray.includes(`${this.path}/${this.name}.cpp`)) return [];
    visitedArray.push(`${this.path}/${this.name}.cpp`);

    if (!fs.existsSync(`${this.path}/${this.name}.hpp`)) return [];

    let fileHeader = fs.readFileSync(`${this.path}/${this.name}.hpp`, "utf8");
    let fileContent = fs.readFileSync(`${this.path}/${this.name}.cpp`, "utf8");
    let dependencies = [];

    // Get all immediate header file dependencies
    let dependenciesFound = [...fileHeader.matchAll(local_dependency_search)];
    dependenciesFound = [...dependenciesFound, ...fileContent.matchAll(local_dependency_search)];
    if (dependenciesFound.length == 0) return [];

    dependenciesFound.forEach((element) => {
      let file = this.path + "/" + element[1].replace(".hpp", ".cpp");
      //console.log(file);
      if (!fs.existsSync(file)) return;
      dependencies.push(path.normalize(file));
    });

    // Recursively return the remaining tree of dependencies

    let newDependencies = [];

    dependencies.forEach((dep) => {
      let more = new CPPObject(dep).getDependencies(false);
      newDependencies = [...newDependencies.concat(more)];
    });

    dependencies = [...new Set(dependencies.concat(newDependencies))];

    dependencies = dependencies.filter(
      (dep) => {
        return dep != path.normalize(`${this.path}/${this.name}.cpp`)
      }
    );

    //console.log(`dependencies for ${this.name}.cpp`, dependencies);

    return dependencies;
  }
}

module.exports = CPPObject;
