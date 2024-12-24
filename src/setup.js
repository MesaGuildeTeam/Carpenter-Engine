/** @namespace Setup */

const child_process = require('child_process');
const utils = require('./utils.js');
const fs = require('node:fs');
const os = require('os');

const packageDir = require.resolve('../package.json');

const scriptExtension = process.platform === 'win32' ? 'bat' : 'sh';

/**
 * Checks if the specified compiler is installed and runs the callback on response
 * 
 * @param {string} program The name of the compiler
 * @param {function} callback The callback to call when the compiler is found
 * @param {boolean} considerLocalPath Whether to search for the compiler from the local home directory
 * 
 * @warning This function will currently check for the compiler your whole drive if considerLocalPath is set to true. It is not recommended for now until the tool knows who the user is.
 * 
 * @memberof Setup
 */
async function findCompiler(program, callback, considerLocalPath) {
  process.stdout.write(`Searching for ${program} in PATH ` + utils.Asciis.Waiting);
  process.stdout.moveCursor(-5, 0);

  await child_process.exec(`which ${program}`, {cwd: process.cwd()}, async (err, stdout, stderr) => {
    if (!err) {
      process.stdout.write(` ${utils.Asciis.Success} `);
      console.log(`${program} found in ${stdout}`);
      callback(true);
      return;
    }

    process.stdout.write(`${utils.Asciis.Fail} `);
    console.log(`${program} not found in path `);

    process.stdout.write(`Searching for ${program} in local ` + utils.Asciis.Waiting);

    fs.stat(os.homedir() + '/.table-engine/emsdk', (err, status) => {
      process.stdout.moveCursor(-5, 0);
      if (err) {
        process.stdout.write(` ${utils.Asciis.Fail} `);
        console.log(`${program} not found in local`);
        callback(false);
        return;
      }

      process.stdout.write(` ${utils.Asciis.Success} `);
      console.log(`${program} found in ${os.homedir()}/.table-engine/emsdk`);
      callback(true);
      return
    })
    
  });
}

/**
 * returns true if the path exists in the project directory
 *  
 * @param {string} path the name of the directory to check
 * @memberof Setup
 */
async function findPathLocal(path) {
  await fs.stat(path, (err, status) => {
    console.log(err != null);
    return err != null;
  })
}

/**
 * Runs the following script from the scripts folder. Uses the appropriate extension based on the OS
 * 
 * @param {string} script The script to run
 * @memberof Setup
 */
async function callShellProgram(script) { 
  let child = await child_process.exec(`sh "${script}.${scriptExtension}"`, {cwd: process.cwd()}, (err, stdout, stderr) => {
    console.log("\x1b[0m");
  });

  child.stdout.on('data', (data) => {
    process.stdout.write("\x1b[2m" + data);
  });

  child.stderr.on('data', (data) => {
    process.stdout.write("\x1b[31m\x1b[0m" + data);
  });

  child.on('exit', (code, signal) => {
    return code;
  });
}

/**
 * Installs Emscripten if it is not installed with the configuration defnined in its parameters 
 * @memberof Setup
 */
function installEmscripten(config = {}) {
  // Check if emscripten is installed first 
  findCompiler('em++', async (result) => {
    if (result) {
      console.log("emsdk has already been setup for table engine", utils.Asciis.Unflip);
    } else {
      console.log(`Installing and/or Activating Emscripten`);
      callShellProgram(__dirname + "/../scripts/installEmcc")
    }

    console.log("Creating directories");
    fs.mkdir(process.cwd() + "/objs", (err) => {
      if (err)
        console.log("objs folder already exists");
    });
    fs.mkdir(process.cwd() + "/build", (err) => {
      if (err)
        console.log("build folder already exists");
    });
  }, false);
}

module.exports = {
  installEmscripten: installEmscripten
}