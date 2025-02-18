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

const local_dependency_search = /#include "(.*?)"/g;

/**
 * A reference class to a compilable `.cpp` file.
 */
class CPPObject {
  /**
   * Default Constructor
   * @param {string} name name of the .cpp file to be compiled
   */
  constructor(name) {
    this.depName = name;
    this.name = path.basename(name, path.extname(name));
    this.path = path.dirname(name);

    this.lastModification = null;
    this.lastBuild = null;

    if (!fs.existsSync(`${this.path}/${this.name}.cpp`)) {
      throw new Error(`File does not exist. ${this.path}/${this.name}.cpp`);
    }

    this.lastModification = fs.statSync(`${this.path}/${this.name}.cpp`, undefined).atimeMs;

    // Ok this one can create an error
    try {
      this.lastBuild = fs.statSync(`${outputLocation}/${this.name}.o`).atimeMs;
    } catch (e) {
      this.lastBuild = null;
    }
  }

  /**
   * Returns a boolean to determine if this file needs to be built
   */
  needsBuild() {
    // check this file and its dependecies
    let tocheck = [this.depName, ...this.dependencies];

    tocheck.forEach((dep) => {
      let depObj = new CPPObject(dep);

      // Don't build if dependency doesn't exist
      if (!fs.existsSync(`${depObj.path}/${depObj.name}.cpp`)) return false;

      if (depObj.lastBuild == null || depObj.lastModification > depObj.lastBuild) {
        return true;
      }
    });

    return false;
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
  get dependencies(){
    // yeah, thats a function in a function

    let dependencies = [];

    // recursivly get dependencies and add them to dependencies
    function getDependenciesR(obj) {
      if (!fs.existsSync(`${obj.path}/${obj.name}.hpp`)) {
        return;
      }
      let fileHeader = fs.readFileSync(`${obj.path}/${obj.name}.hpp`, "utf8");
    
      // Get all immediate header file dependencies
      [...fileHeader.matchAll(local_dependency_search)].forEach((element) => {
        // Get file dep name and check existence
        let file = obj.path + "/" + element[1].replace(".hpp", ".cpp");
        if (!fs.existsSync(file)) return;
        let dep = path.normalize(file);
        // add dependency
        if (!(dependencies.includes(dep))) {
          dependencies.push(dep);
          // add subdependencies
          getDependenciesR(new CPPObject(dep));
        }
      });
    }

    // fill dependencies
    getDependenciesR(this);

    // filter out this file from its dependencies
    return dependencies.filter(dep => dep !== this.depName);
  }
}

module.exports = CPPObject;
