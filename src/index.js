const setup = require('./setup.js');
const pkg = require('../package.json');
const utils = require('./utils.js');
const build = require('./build.js');

// Debug to see what the arguments are
//console.log(process.argv);
const title = `  ${utils.Asciis.Table} Table Engine v${pkg.version} ${utils.Asciis.Table}
-----------------${'-'.repeat(pkg.version.length)}---------
${pkg.description}\n`

const usage = `Usage: table <command> [options]\n`
  
const commands = `Commands:
  setup   Check and install emscripten to compile the project

  build   Build the project with the configuration used. If no configuration is provided, the complete build process will be used
  options:
    -b    Run the build process and convert the .cpp files into modules
    -l    Link all the files together
    -p    Package the static html into the project
`

function ShowHelp() {
  console.log(usage);
  console.log(commands);
}

// Process Arguments

if (process.argv.length <= 2) {
  console.log(title);
  ShowHelp();
  return process.exit(0);
}

console.log("Working in", process.cwd(), "On platform", process.platform)

switch (process.argv[2]) {
  case 'setup': 
    return setup.installEmscripten();
  case 'build': 
    return build.buildGame(build.processArgs(process.argv.slice(3, process.argv.length)));
  default:
    console.error(`${utils.Asciis.TableFlipper} Unknown command ${process.argv[2]}\n`);
    ShowHelp();
    return process.exit(1);
}

return process.exit(0);