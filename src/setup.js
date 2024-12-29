/** @namespace Setup */

const child_process = require('child_process');
const utils = require('./utils.js');
const fs = require('node:fs');
const os = require('os');

const packageDir = require.resolve('../package.json');

const scriptExtension = process.platform === 'win32' ? 'ps1' : 'sh';

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
  let child = await child_process.exec(`${process.platform === 'win32' ? "powershell.exe -File " : "sh "}"${script}.${scriptExtension}"`, {cwd: process.cwd()}, (err, stdout, stderr) => {
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
  // Install/Update Emscripten
  console.log(`Installing/Updating Emscripten`);
  callShellProgram(__dirname + "/../scripts/installEmcc") 

  console.log("Creating directories");
  fs.mkdir(process.cwd() + "/objs", (err) => {
    if (err)
      console.log("objs folder already exists");
  });
  fs.mkdir(process.cwd() + "/build", (err) => {
    if (err)
      console.log("build folder already exists");
  });
}

module.exports = {
  installEmscripten: installEmscripten
}