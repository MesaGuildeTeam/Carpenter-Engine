const express = require('express');
const server = express();

const utils = require('../utils');

var buildConfig;

try {
  buildConfig = require(process.cwd() + '/tableconf.json') 
} catch (exception) {
  buildConfig = {};
};

// Adding the game testing environment 

server.use("/runtime", express.static(buildConfig.static));

server.get("/runtime/engine.wasm", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.wasm");
});

server.get("/runtime/engine.js", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.js");
});

server.get("/runtime/engine.data", (req, res) => {
  res.sendFile(process.cwd() + "/build/engine.data");
});

server.use("/Assets", express.static("./Assets"));

server.listen(3000, () => {
  console.log("\nDevelopment environment is now running!", utils.Asciis.Success);
  console.log("Test your game at: http://localhost:3000/runtime");
});