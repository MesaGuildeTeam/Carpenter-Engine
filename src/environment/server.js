/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

const express = require("express");
const server = express();

const utils = require("../utils");

var buildConfig;

try {
  buildConfig = require(process.cwd() + "/tableconf.json");
} catch (exception) {
  buildConfig = {};
}

// Adding the game testing environment

server.use("/runtime", express.static(buildConfig.static));

server.get("/runtime/engine.wasm", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.wasm");
});

server.get("/runtime/engine.wasm.map", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.wasm.map");
});

server.get("/runtime/engine.js", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.js");
});

server.get("/runtime/engine.data", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.data");
});

server.use("/runtime/Assets", express.static("./Assets"));

// Debugging Folders

//server.use("/", express.static("./"));
server.use("/src/", express.static("./src/"));
server.use("/examples/", express.static("./examples/"));

function runServer() {
  server.listen(3000, () => {
    console.log(
      "\nDevelopment environment is now running!",
      utils.Asciis.Success,
    );
    console.log("Test your game at: http://localhost:3000/runtime");
  });
}

module.exports = runServer;
