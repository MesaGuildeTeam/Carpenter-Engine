/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

const os = require("os");
const fs = require("fs");
const path = require("path");

const utils = require("../utils");
const CPPObject = require("./CPPObject");

let buildConfig;

try {
  buildConfig = require(process.cwd() + "/tableconf.json");
} catch (exception) {
  buildConfig = {};
}

const EMCC =
  process.platform == "win32"
    ? os.homedir() + "\\.mesaguilde\\emsdk\\upstream\\emscripten\\em++.bat"
    : "~/.mesaguilde/emsdk/upstream/emscripten/em++";

const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/@mesaguilde/carpenter-engine/src/engine/";

const test_dependency_search = /#include <([A-Za-z0-9\/\\]+).hpp>/g;

/**
 * @brief A reference class to a compilable `.cpp` test file.
 * Similarily to a CPPObject, this class also builds the file if it has not been
 * built since it's last modification. However, this file assumes its directory
 * is "./tests/CPP", so it will look for dependencies in "./src/" instead.
 *
 * @author Roberto Selles
 */
class CPPTest extends CPPObject {
  /**
   * default constructor of the test file
   * @param {string} name the name of the test
   */
  constructor(name) {
    super(name);

    try {
      this.lastBuild = fs.statSync(`./tests/WASM/${this.name}.js`).atimeMs;
    } catch (e) {
      this.lastBuild = null;
    }
  }

  /**
   * Builds the test file to be tested
   */
  build() {
    if (!this.needsBuild()) return;

    let files = "";
    this.getDependencies().forEach((dep) => {
      let file = new CPPObject(dep);
      files = files + `"./objs/${file.name}.o" `;
    });

    fs.mkdirSync("./tests/WASM", { recursive: true });

    let execCmd = `${EMCC} "${this.path}/${this.name}.cpp" ${files} -o "./tests/WASM/${this.name}.js" -std=c++20 -I${includeDir} -DTESTNAME="${this.path}/${this.name}.cpp" -sEXPORTED_FUNCTIONS=_Testing_getTestCount,_Testing_getPassedTestCount,_Testing_runTests,_main -sMODULARIZE -sALLOW_MEMORY_GROWTH -g -gsource-map`;

    utils.execCommand(execCmd, `Compiling test ${this.name}.cpp`);
  }

  /**
   * asynchronously runs the test file
   * @returns {boolean} a promise that returns true if the test passed
   */
  async run() {
    let test = require("../../tests/WASM/" + this.name + ".js");

    const runtime = await test().then((instance) => {
      instance._Testing_runTests();

      let testCount = instance._Testing_getTestCount();
      let passed = instance._Testing_getPassedTestCount();
      let failed = testCount - passed;

      console.log(
        `${passed} passed, ${failed} failed, ${testCount} total ${passed == 0 ? utils.Asciis.TableFlip : ""}`,
      );

      return passed == testCount;
    });

    return runtime;
  }

  /**
   * Returns an array of all the .cpp files required to build this test
   *
   * @warn This process assumes the file has a .hpp file along with the .cpp file. Please code as if you were programming with OOP
   * @returns {String[]} Array of cpp files that this one depends on
   */
  getDependencies() {
    let fileData = fs.readFileSync(`${this.path}/${this.name}.cpp`, "utf8");
    let dependencies = [];

    // Get all immediate header files
    let dependenciesFound = [...fileData.matchAll(test_dependency_search)];
    /*console.log(
      `Dependencies for Test ${this.name}.cpp:`,
      dependenciesFound.length,
    );*/

    dependenciesFound.forEach((element) => {
      //console.log(element[1]);
      let file = buildConfig.inputPath + "/" + element[1] + ".cpp";
      if (fs.existsSync(file)) dependencies.push(path.normalize(file));
    });

    // Recursively return the remaining tree of dependencies
    if (dependencies.length != 0) {
      let newDependencies = [];
      dependencies.forEach((dep) => {
        let more = new CPPObject(dep).getDependencies(true);
        newDependencies = [...new Set(newDependencies.concat(more))];
      });

      dependencies = [...new Set(dependencies.concat(newDependencies))];
    }

    //console.log("Dependencies:", dependencies);

    return dependencies;
  }
}

module.exports = CPPTest;
