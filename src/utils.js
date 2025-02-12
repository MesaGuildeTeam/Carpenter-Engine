/**
 * Some cute table themed utils to decorate the game engine
 * 
 * @author Roberto Selles
 */

// Modules 
const fs = require('fs');
const path = require('path');

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

module.exports = {
  Asciis: Asciis,
  throwError: throwError,
  processFiles: processFiles
};