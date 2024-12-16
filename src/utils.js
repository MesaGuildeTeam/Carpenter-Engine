/**
 * Some cute table themed utils to decorate the game engine
 * 
 * @author Roberto Selles
 */

const Table = "┬─┬"
const FlippedTable = "┴─┴"
const TableFlipper = "(╯°□°)╯︵ ┻━┻"

function throwError(message) {
  console.error("An error has occured" + TableFlipper + "\n\n" + message);
}

module.exports = {
  Table: Table,
  FlippedTable: FlippedTable,
  TableFlipper: TableFlipper,
  throwError: throwError
};