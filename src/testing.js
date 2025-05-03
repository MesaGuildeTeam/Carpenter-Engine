/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/** @namespace Testing */

const fs = require("fs");

const utils = require("./utils");
const CPPTest = require("./classes/CPPTest");

/**
 * Runs all tests and outputs the results
 * @returns {process} The exit code
 * @namespace Testing
 * @author Roberto Selles
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
