import java.io.File

import DS.*

fun main() {
    var maze : Maze = Maze(10)
    File("data.txt").writeText(maze.generateMaze(1).toStr())
}