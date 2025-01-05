const { Command } = require('commander');
const program = new Command();

const setup = require('./setup.js');
const pkg = require('../package.json');
const utils = require('./utils.js');
const build = require('./build.js');

program.name('table')
  .description(pkg.description)
  .version(pkg.version);

program.command('setup')
  .description('setup your environment by installing emscripten and creating the necessary folders')
  .action(() => {
    setup.installEmscripten();
  });

program.command('build')
  .description('build the project using the configuration in tableconf.json or the default configuration. If no step are defined, the complete build process will be used.')
  .option('-c, --compile', 'Compile the .cpp files into wasm .o files')
  .option('-l, --link', 'Link all the files together')
  .option('-p, --package', 'Package the static webpage into the project')
  .action((options) => {
    if (options.length > 0) {
      build.buildGame();
      return;
    }
    build.buildGame({runBuild: options.compile, runLink: options.link, runPackage: options.package});
  });

program.parse();