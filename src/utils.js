/**
 * Some cute table themed utils to decorate the game engine
 * 
 * @author Roberto Selles
 */

// Modules 
const fs = require('fs');
const path = require('path');
const child_process = require('child_process');

/**
 * The ascii table used to decorate the game engine
 */
const Asciis = {
  Table: "┬─┬",
  FlippedTable: "┴─┴",
  TableFlip: "(╯°□°)╯︵ ┴─┴",
  Unflip: "┬─┬ノ( º _ ºノ)",
  Success: "\x1b[32m[✓]\x1b[0m",
  Fail: "\x1b[31m[X]\x1b[0m",
  Waiting: "\x1b[33m[⌛︎]\x1b[0m",
}

var verbose = false;

/**
 * Configures the CLI to be verbose about its actions.
 * @param {boolean} value 
 */
function setVerbose(value = true) {
  verbose = value;
}

/**
 * A customized string that throws a funny error message
 * 
 * @param {string} message 
 */
function throwError(message) {
  console.error("An error has occured" + Asciis.TableFlip + "\n\n" + message);
}

/**
 * Recursive function
 * 
 * Gets every file with the extension from a certain directory and its child folders and runs a callback on it
 * 
 * @param {string} folder The folder to start the recursive search from
 * @param {string} extension The extension to look for
 * @param {function} callback The callback to run
 */
function processFiles(folder, extension, callback) {
  fs.readdirSync(folder).forEach(file => {
    if (fs.statSync(path.join(folder, file)).isDirectory()) {
      processFiles(path.join(folder, file), extension, callback);
    } else if (extension == "") {
      callback(file, folder);
    } else if (file.endsWith(extension)) {
      callback(file.split('.')[0], folder);
    }
  })
}

/**
 * Runs the following command as a process. The output is printed to the console in a nice format readable by the user
 * 
 * @param {string} script The command to run
 * @param {string} message The message to print
 */
function execCommand(script, message = "Running") {
  try {
    process.stdout.write(message);

    let output = child_process.execSync(script, {cwd: process.cwd(), stdio: ['ignore', 'pipe', 'pipe']});

    process.stdout.write(" " + Asciis.Success + "\n");

    if (verbose)
      console.log("\x1b[2m" + script, "\x1b[0m");

    if (output == "")
      return;

    console.log("\x1b[2m" + output.toString(), "\x1b[0m");
  } catch (error) {
    process.stdout.write(" " + Asciis.Fail + "\n");

    if (verbose)
      console.log("\x1b[2m" + script, "\x1b[0m");
    
    console.log("\x1b[31;2m" + error, "\x1b[0m");
    process.exit(1);
  }
}

module.exports = {
  Asciis: Asciis,
  throwError: throwError,
  processFiles: processFiles,
  execCommand: execCommand,
  setVerbose: setVerbose
};