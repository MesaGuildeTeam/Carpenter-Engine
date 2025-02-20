const { assert } = require("console");
const CPPObject = require("../src/classes/CPPObject");
const fs = require("fs");
const path = require("path");

describe("Testing the CPPObject with src/engine/Game.cpp", () => {
  let obj;

  test("Test the constructor", () => {
    obj = new CPPObject("./src/engine/Game.cpp");
  });

  test("Test if the file needs a rebuild", () => {
    if (obj.needsBuild())
      console.warn(
        "The game engine should be built before testing this component",
      );

    expect(obj.needsBuild()).toBe(false);
  });

  test("Return Dependency Tree", () => {
    let deps = obj.getDependencies(true);

    expect(deps).toStrictEqual([
      path.normalize("src/engine/Node.cpp"),
      path.normalize("src/engine/Renderer.cpp"),
      path.normalize("src/engine/Utils.cpp"),
    ]);
  });
});

describe("Testing the CPPObject with src/engine/UI/UIButton.cpp", () => {
  let obj = new CPPObject("./src/engine/UI/UIButton.cpp");

  test("Return Dependency Tree", () => {
    let deps = obj.getDependencies();

    expect(deps).toStrictEqual([
      path.normalize("src/engine/UI/UILabel.cpp"),
      path.normalize("src/engine/UI/UIElement.cpp"),
      path.normalize("src/engine/Node.cpp"),
      path.normalize("src/engine/Utils.cpp"),
    ]);
  });
});
