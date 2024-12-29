/**
 * Some cute table themed utils to decorate the game engine
 * 
 * @author Roberto Selles
 */

const Asciis = {
  Table: "┬─┬",
  FlippedTable: "┴─┴",
  TableFlip: "(╯°□°)╯︵ ┻━┻",
  Unflip: "┬─┬ノ( º _ ºノ)",
  Success: "\x1b[32m[✓]\x1b[0m",
  Fail: "\x1b[31m[X]\x1b[0m",
  Waiting: "\x1b[33m[⌛︎]\x1b[0m",
}

function throwError(message) {
  console.error("An error has occured" + Asciis.TableFlip + "\n\n" + message);
}

module.exports = {
  Asciis: Asciis,
  throwError: throwError
};