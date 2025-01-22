const CPPObject = require("./CPPObject");
const os = require("os");
const fs = require("fs");
const child_process = require("child_process");
const path = require("path");

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

  build() {
    if (!this.needsBuild()) return;

    let files = "";
    this.dependencies.forEach((dep) => {
      let file = new CPPObject(dep);
      file.build();
      files = files + `"${file.path}/${file.name}.o"`;
    });
    
    fs.mkdirSync("./tests/WASM", { recursive: true });

    let execCmd = `${EMCC} "${this.path}/${this.name}.cpp" ${files} -o "./tests/WASM/${this.name}.js" -std=c++20 -I${includeDir} -DTESTNAME="${this.path}/${this.name}.cpp"`;

    console.log(`Building test ${this.name}.cpp with em++`);
    console.log(execCmd);

    child_process.execSync(execCmd, { cwd: process.cwd() });
  }

  run(callback) {
    let folder = "../../tests/WASM/" + this.name + ".js";
    
    import(folder).then((test) => {
      if (callback != null) callback();
    });
  }
}

module.exports = CPPTest;