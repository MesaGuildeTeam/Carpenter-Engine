/**
 * Javascript module that sets up the game development environment for the game engine
 */

const child_process = require('child_process');
const utils = require('./utils.js');
const fs = require('node:fs');
const path = require('path');

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
 */
async function findCompiler(program, callback, considerLocalPath) {
  process.stdout.write(`Searching for ${program} in PATH ` + utils.Asciis.Waiting);
  process.stdout.moveCursor(-5, 0);

  await child_process.exec(`which ${program}`, async (err, stdout, stderr) => {
    if (!err) {
      process.stdout.write(` ${utils.Asciis.Success} `);
      console.log(`${program} found in ${stdout}`);
      callback(true);
      return;
    }

    process.stdout.write(`${utils.Asciis.Fail} `);
    console.log(`${program} not found in path `);

    process.stdout.write(`Searching for ${program} in local` + utils.Asciis.Waiting);

    await child_process.exec(`find ./ -name ${program}`, async(err, stdout, stderr) => {
      process.stdout.moveCursor(-5, 0);
    
      if (!err && stdout.length > 0) {
        process.stdout.write(` ${utils.Asciis.Success} `);
        console.log(`${program} found in ${stdout}`);
        callback(true);
        return;
      }

      process.stdout.write(` ${utils.Asciis.Fail} `);
      console.log(`${program} not found in project`);
      
      if (!considerLocalPath) {
        callback(false);
        return;
      } 
      
      if (considerLocalPath) {
      process.stdout.write(`Searching for ${program} in local` + utils.Asciis.Waiting);
        await child_process.exec(`find ~/ -name ${program}`, (err, stdout, stderr) => {
          process.stdout.moveCursor(-5, 0);
        
          if (!err && stdout.length > 0) {
            process.stdout.write(` ${utils.Asciis.Success} `);
            console.log(`${program} found in ${stdout}`);
            callback(true);
            return;
          }

          process.stdout.write(` ${utils.Asciis.Fail} `);
          console.log(`${program} not found in local path`);
          callback(false);
          return;
        })
      }
    });
  });
}

function findPathLocal(folder) {
  fs.stat(folder, (err, status) => {
    return err != null;
  })
}

/**
 * Installs Emscripten if it is not installed
 */
async function callShellProgram(script) { 
  let child = await child_process.exec(`sh "${script}.${scriptExtension}"`, (err, stdout, stderr) => {
    console.log("\x1b[0m");
  });

  child.stdout.on('data', (data) => {
    process.stdout.write("\x1b[2m" + data);
  });

  child.stderr.on('data', (data) => {
    process.stdout.write("\x1b[31m\x1b[0m" + data);
  });
}

async function installEmscripten(config = {}) {
  // Check if emscripten is installed first 
  findCompiler('em++', (result) => {
    if (findPathLocal("emsdk") || result) {
      console.log("emsdk has already been downloaded", utils.Asciis.Unflip);
    } else {
      console.log(`Downloading Emscripten`);
      callShellProgram(process.cwd() + "/scripts/downloadEmcc")
    }

    console.log(`Installing/Updating Emscripten`);
    callShellProgram(process.cwd() + "/scripts/installEmcc")

  }, false);
}

module.exports = {
  installEmscripten: installEmscripten
}