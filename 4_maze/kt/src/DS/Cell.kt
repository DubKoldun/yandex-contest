package DS

enum class Wall {
    BREAK, ENTIRE
}

class Cell () {
    var neighbors: MutableList<Cell> = mutableListOf<Cell>()
    var walls : MutableMap<Cell, Wall> = mutableMapOf<Cell, Wall>()
    var isVisited : Boolean = false
}