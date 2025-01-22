const fs = require("fs");
const path = require("path");

const utils = require("./utils");
const CPPTest = require("./classes/CPPTest");

function RunTests() {
  utils.processFiles("./tests/CPP", ".cpp", (file, folder) => {
    let test = new CPPTest("./tests/CPP/" + file + ".cpp");
    test.build();
    test.run();
  });
}

module.exports = {
  RunTests: RunTests
}