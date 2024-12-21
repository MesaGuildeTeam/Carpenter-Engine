/**
 * The main runtime script for the game engine toolkit
 */

const setup = require('./setup.js');
const pkg = require('../package.json');
const utils = require('./utils.js');

// Debug to see what the arguments are
//console.log(process.argv);
const title = `  ${utils.Asciis.Table} Table Engine v${pkg.version} ${utils.Asciis.Table}
-----------------${'-'.repeat(pkg.version.length)}---------
${pkg.description}\n`

const usage = `Usage: table <command> [options]\n`
  
const commands = `Commands:
  setup      Setup the game engine environment
`

function ShowHelp() {
  console.log(usage);
  console.log(commands);
}

// Process Arguments

if (process.argv.length <= 2) {
  console.log(title);
  ShowHelp();
  return 0;
}

switch (process.argv[2]) {
  case 'setup': 
    setup.installEmscripten(); 
    return 0;
  default:
    console.error(`${utils.Asciis.TableFlipper} Unknown command ${process.argv[2]}\n`);
    ShowHelp();
    throw 1;
}
