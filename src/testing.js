/** @namespace Testing */

const fs = require("fs");

const utils = require("./utils");
const CPPTest = require("./classes/CPPTest");

/**
 * Runs all tests and outputs the results
 * @namespace Testing
 */
async function RunTests() {
  let passedSuites = 0;
  let suiteCount = 0;

  let files = fs.readdirSync("./tests/CPP");

  const filePromise = files.map(async (file) => {
    let test = new CPPTest("./tests/CPP/" + file);
    test.build();
    suiteCount++;
    await test.run().then((result) => {
      passedSuites += result;
    });
  });

  await Promise.all(filePromise).then(() => {
    console.log(
      `\nSuites: ${passedSuites} passed, ${suiteCount - passedSuites} failed, ${suiteCount} total ${passedSuites == 0 ? utils.Asciis.TableFlip : ""}`,
    );

    if (passedSuites != suiteCount) process.exit(1);
    else process.exit(0);
  });
}

module.exports = {
  RunTests: RunTests,
};
