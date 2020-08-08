#include <ctime>
#include <vector>
#include <cstdio>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::cin;

const size_t MAZE_SIZE = 100;

void printMaze(vector<vector<char>> const& maze) {
    for (auto const& raw: maze) {
        for (auto const& block: raw) {
            cout << block;
        }
        cout << "\n";
    }
}

int main() {
    srand(time(NULL));

    vector<vector<char>> maze(2 * MAZE_SIZE + 2, vector<char>(2 * MAZE_SIZE + 1));

    // generate border of maze
    for (size_t i = 1; i < maze[1].size(); ++i) {
        maze[1][i] = static_cast<bool>(i % 2) ? '-' : '+';
        maze[maze.size()-1][i] = static_cast<bool>(i % 2) ? '-' : '+';
    }

    for (size_t i = 1; i < maze[1].size(); ++i) {
        maze[i][1] = static_cast<bool>(i % 2) ? '|' : '+';
        maze[i][maze.size()-1] = static_cast<bool>(i % 2) ? '|' : '+';
    }

    // generate rest of maze
    for (size_t i = 2; i < 2 * MAZE_SIZE + 1; ++i) {
        for (size_t j = 2; j < 2 * MAZE_SIZE + 1; ++j) {

            if (i % 2 == 0) {

                if (j % 2 == 0) {
                    maze[i][j] = '+';
                } else {
                    maze[i][j] = static_cast<bool>(rand() % 2) ? '.' : '-';
                }

            } else {

                if (j % 2 == 0) {

                    maze[i][j] = static_cast<bool>(rand() % 2) ? '.' : '|';
                } else {
                    maze[i][j] = '.';

                }

            }

        }

    }

    printMaze(maze);
}
