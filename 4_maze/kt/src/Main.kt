import DS.*

fun main() {
    var maze : Maze = Maze(2)
    println(maze.toStr())
    println(maze.generateMaze().toStr())
}