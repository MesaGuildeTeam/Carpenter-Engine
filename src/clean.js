/** @namespace Clean */

const fs = require('fs');
const utils = require('./utils');

/**
 * Cleans the files built by the build process
 * @memberof Clean
 */
function clean() {
  console.log("Cleaning objs and build folders");
  utils.processFiles("./objs", ".o", (file, folder) => {
    fs.rmSync(folder + "/" + file + ".o", { recursive: true, force: true });
  });

  utils.processFiles("./build", "", (file, folder) => {
    fs.rmSync(folder + "/" + file, { recursive: true, force: true });
  });

  utils.processFiles("./tests/WASM", ".js", (file, folder) => {
    fs.rmSync(folder + "/" + file + ".js", { recursive: true, force: true });
    fs.rmSync(folder + "/" + file + ".wasm", { recursive: true, force: true });
  });
}

module.exports = {
  clean: clean
}