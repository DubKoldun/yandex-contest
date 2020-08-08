package DS

class Maze(val size: Int) {
    private var grid : MutableList<MutableList<Cell>> 
    private val MAZE_SIZE : Int

    init {
        MAZE_SIZE = 2 * size + 1
        grid = MutableList(size) { MutableList(size) { Cell() } }

        // init corners
        grid[0][0].neighbors.addAll(listOf(grid[0][1], grid[1][0]))
        grid[0][0].walls.putAll(listOf(Pair(grid[0][1], Wall.ENTIRE), Pair(grid[1][0], Wall.ENTIRE)))

        grid[size-1][size-1].neighbors.addAll(listOf(grid[size-2][size-1], grid[size-1][size-2]))
        grid[size-1][size-1].walls.putAll(listOf(Pair(grid[size-2][size-1], Wall.ENTIRE), Pair(grid[size-1][size-2], Wall.ENTIRE)))

        grid[0][size-1].neighbors.addAll(listOf(grid[1][size-1], grid[0][size-2]))
        grid[0][size-1].walls.putAll(listOf(Pair(grid[1][size-1], Wall.ENTIRE), Pair(grid[0][size-2], Wall.ENTIRE)))

        grid[size-1][0].neighbors.addAll(listOf(grid[size-2][0], grid[size-1][1]))
        grid[size-1][0].walls.putAll(listOf(Pair(grid[size-2][0], Wall.ENTIRE), Pair(grid[size-1][1], Wall.ENTIRE)))

        // init borders
        for (i in 1..size-2) {
            grid[0][i].neighbors.addAll(listOf(grid[0][i-1], grid[0][i+1], grid[1][i]))
            grid[0][i].walls.putAll(listOf(Pair(grid[0][i-1], Wall.ENTIRE), Pair(grid[0][i+1], Wall.ENTIRE), Pair(grid[1][i], Wall.ENTIRE)))

            grid[i][0].neighbors.addAll(listOf(grid[i][1], grid[i+1][0], grid[i-1][0]))
            grid[i][0].walls.putAll(listOf(Pair(grid[i][1], Wall.ENTIRE), Pair(grid[i+1][0], Wall.ENTIRE), Pair(grid[i-1][0], Wall.ENTIRE)))

            grid[size-1][i].neighbors.addAll(listOf(grid[size-1][i-1], grid[size-1][i+1], grid[size-2][0]))
            grid[size-1][i].walls.putAll(listOf(Pair(grid[size-1][i-1], Wall.ENTIRE), Pair(grid[size-1][i+1], Wall.ENTIRE), Pair(grid[size-2][0], Wall.ENTIRE)))

            grid[i][size-1].neighbors.addAll(listOf(grid[i][size-2], grid[i+1][size-1], grid[i-1][size-1]))
            grid[i][size-1].walls.putAll(listOf(Pair(grid[i][size-2], Wall.ENTIRE), Pair(grid[i+1][size-1], Wall.ENTIRE), Pair(grid[i-1][size-1], Wall.ENTIRE)))

        }

        // init main part 
        for (i in 1..size-2) {
            for (j in 1..size-2) {
                   grid[i][j].neighbors.addAll(listOf(grid[i-1][j], grid[i+1][j], grid[i][j-1], grid[i][j+1]))
                   grid[i][j].walls.putAll(listOf(Pair(grid[i-1][j], Wall.ENTIRE), Pair(grid[i+1][j], Wall.ENTIRE), Pair(grid[i][j-1], Wall.ENTIRE), Pair(grid[i][j+1], Wall.ENTIRE)))
            }
        }
    }

    private fun defaultMaze() : Maze {
       for (row in grid) {
           for (item in row) {
               item.walls.mapValues { Wall.ENTIRE }
           }
       }
       return this
    }

    private fun randomByDfs() : Maze {
        var stack : MutableList<Cell> = MutableList(1) { grid[0][0] }
        grid[0][0].isVisited = true;

        
        while (stack.isNotEmpty()) {
            val currentCell : Cell  = stack.get(stack.size-1) 
            stack.remove(currentCell)

            for (neighbor in currentCell.neighbors) {
                if (!neighbor.isVisited) {
                    stack.add(neighbor)
                    currentCell.walls[neighbor] = Wall.BREAK
                    neighbor.walls[currentCell] = Wall.BREAK
                    neighbor.isVisited = true
                }
            }
        }

        return this
    }

    fun generateMaze(type: Int = 0) : Maze {
        return when (type) {
            1 -> randomByDfs()
            else -> defaultMaze()
        }
    }

    fun toStr() : String {
        var ans : String = ""

        // generate top border of maze
        for (i in 0..MAZE_SIZE-1) {
            ans += if (i % 2 == 0) '+' else '-'
        }
        ans += '\n'

        // main part of a maze
        for (i in 1..MAZE_SIZE-2) {

            // left border
            ans += if (i % 2 == 0)  '+' else '|'

            // generate plot by entries
            for (j in 1..MAZE_SIZE-2) {
                val cell_i: Int = (i-1)/2
                val cell_j: Int = (j-1)/2
                val cell = grid[cell_i][cell_j]
            
                if (i % 2 == 0) 
                    ans += if (j % 2 == 0) '+' else 
                        when (cell.walls[grid[cell_i+1][cell_j]]) {
                            Wall.BREAK -> '.'
                            else -> '-'
                        }
                else 
                    ans += if (j % 2 == 1) '.' else 
                        when (cell.walls[grid[cell_i][cell_j+1]]) {
                            Wall.BREAK -> '.'
                            else -> '|'
                        }           
            }

            // right border
            ans += if (i % 2 == 0) "+\n" else "|\n"
        }
        
        // generate bottom border
        for (i in 0..MAZE_SIZE-1) {
            ans += if (i % 2 == 0)  '+' else '-'
        }

        return ans
    }
}
