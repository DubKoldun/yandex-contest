import java.io.File

import DS.*

fun main() {
    var maze : Maze = Maze(100)
    File("ans.txt").writeText(maze.generateMaze(1).toStr())
}