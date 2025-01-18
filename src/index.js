const { Command } = require("commander");
const program = new Command();

const setup = require("./setup.js");
const pkg = require("../package.json");
const utils = require("./utils.js");
const build = require("./build.js");
const clean = require("./clean.js");

const title = `  ${utils.Asciis.Table} Table Engine v${pkg.version} ${utils.Asciis.Table}
-----------------${"-".repeat(pkg.version.length)}---------`;

program
  .name("table")
  .description(pkg.description)
  .version(pkg.version, "-v, --version")
  .addHelpText("beforeAll", title);

// Environment Setup Command
program
  .command("setup")
  .description(
    "setup your environment by installing emscripten and creating the necessary folders",
  )
  .action(() => {
    setup.installEmscripten();
  });

// Build Command
program
  .command("build")
  .description(
    "build the project using the configuration in tableconf.json or the default configuration. If no step are defined, the complete build process will be used.",
  )
  .option("-c, --compile", "Compile the .cpp files into wasm .o files")
  .option("-l, --link", "Link all the files together")
  .option(
    "-p, --package",
    "Package the static webpage into the build ready for distribution",
  )
  .action((options) => {
    if (Object.keys(options).length == 0) {
      build.buildGame();
      return;
    }
    build.buildGame({
      runBuild: options.compile,
      runLink: options.link,
      runPackage: options.package,
    });
  });

program
  .command("dev")
  .description(
    "Run the development and testing environment for the game engine",
  )
  .action(() => {
    require("./environment/server");
  });

// Cleans the project
program
  .command("clean")
  .description(
    "clean the files built by the build process \x1b[2m" +
      utils.Asciis.TableFlip +
      "\x1b[0m",
  )
  .action(() => {
    clean.clean();
  });

program.parse();
