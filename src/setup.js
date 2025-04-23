/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/** @namespace Setup */

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
 * @author Roberto Selles
 */
async function findPathLocal(path) {
  await fs.stat(path, (err, status) => {
    console.log(err != null);
    return err != null;
  })
}

/**
 * Installs Emscripten if it is not installed with the configuration defnined
 * in its parameters
 *  
 * @param {Object} config the configuration object (currently unused) 
 * @memberof Setup
 * @author Roberto Selles
 */
function installEmscripten(config = {}) {
  // Install/Update Emscripten
  command = `${process.platform === 'win32' ? "powershell.exe -File " : "sh "}"${__dirname}/../scripts/installEmcc.${scriptExtension}"`;
  utils.execCommand(command, "Installing/Updating Emscripten"); 

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