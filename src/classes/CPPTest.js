const os = require("os");
const fs = require("fs");
const child_process = require("child_process");
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
    ? os.homedir() + "\\.table-engine\\emsdk\\upstream\\emscripten\\em++.bat"
    : "~/.table-engine/emsdk/upstream/emscripten/em++";

const includeDir =
  buildConfig.includeDir != null
    ? buildConfig.includeDir
    : "node_modules/table-engine/src/engine/";

const test_dependency_search = /#include <([A-Za-z0-9\/\\]+)\.hpp>/g;

/**
 * A reference class to a compilable `.cpp` test file.
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
    this.dependencies.forEach((dep) => {
      let file = new CPPObject(dep);
      file.build();
      files = files + `"./objs/${file.name}.o"`;
    });
    
    fs.mkdirSync("./tests/WASM", { recursive: true });

    let execCmd = `${EMCC} "${this.path}/${this.name}.cpp" ${files} -o "./tests/WASM/${this.name}.js" -std=c++20 -I${includeDir} -DTESTNAME="${this.path}/${this.name}.cpp" -sEXPORTED_FUNCTIONS=_getTestCount,_getPassedTestCount,_main -sMODULARIZE`;

    console.log(execCmd);

    console.log(`Building test: ${this.name}.cpp`);

    child_process.execSync(execCmd, { cwd: process.cwd() });
  }

  /**
   * asynchronously runs the test file 
   * @returns {boolean} a promise that returns true if the test passed 
   */
  async run() {
    let test = require("../../tests/WASM/" + this.name + ".js");

    const runtime = await test().then((instance) => {
      let testCount = instance._getTestCount();
      let passed = instance._getPassedTestCount();
      let failed = testCount - passed;

      console.log(`${this.name}: ${passed} passed, ${failed} failed, ${testCount} total ${passed == 0 ? utils.Asciis.TableFlip : ""}`);

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
  get dependencies() {
    let fileData = fs.readFileSync(`${this.path}/${this.name}.cpp`, "utf8");
    let dependencies = [];

    // Get all immediate header file dependencies
    [...fileData.matchAll(test_dependency_search)].forEach((element) => {
      let file = buildConfig.inputPath + "/" + element[1] + ".cpp";
      console.log(file);
      if (fs.existsSync(file)) 
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

module.exports = CPPTest;