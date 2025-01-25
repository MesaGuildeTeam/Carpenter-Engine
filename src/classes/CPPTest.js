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


/**
 * A reference class to a compilable `.cpp` test file.
 */
class CPPTest extends CPPObject {

  constructor(name) {
    super(name);

    try {
      this.lastBuild = fs.statSync(`./tests/WASM/${this.name}.js`).atimeMs;
    } catch (e) {
      this.lastBuild = null;
    }
  }

  build() {
    if (!this.needsBuild()) return;

    let files = "";
    this.dependencies.forEach((dep) => {
      let file = new CPPObject(dep);
      file.build();
      files = files + `"${file.path}/${file.name}.o"`;
    });
    
    fs.mkdirSync("./tests/WASM", { recursive: true });

    let execCmd = `${EMCC} "${this.path}/${this.name}.cpp" ${files} -o "./tests/WASM/${this.name}.js" -std=c++20 -I${includeDir} -DTESTNAME="${this.path}/${this.name}.cpp" -sEXPORTED_FUNCTIONS=_getTestCount,_getPassedTestCount,_main -sMODULARIZE`;

    console.log(`Building test: ${this.name}.cpp`);

    child_process.execSync(execCmd, { cwd: process.cwd() });
  }

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
}

module.exports = CPPTest;