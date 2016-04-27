/*
 * main.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

const int rows = 20, cols = 20;

int offset[8][2]{
    { 0,  1},
    { 1,  1},
    { 1,  0},
    { 1, -1},

    { 0, -1},
    {-1, -1},
    {-1,  0},
    {-1,  1},
};
int get_heighbors(int world[rows][cols], int row, int col) {
    int neighbors = 0;
    for(int o = 0; o < 8; ++o){
        int r = row + offset[o][0];
        int c = col + offset[o][1];

        r = r >= rows ? 0 :
            r < 0 ? rows - 1 :
            r;

        c = c >= cols ? 0 :
            c < 0 ? cols - 1 :
            c;

        neighbors += world[r][c];
    }

    return neighbors;
}

int main(int argc, char* argv[]) {
    try {
        cout << "Conway's life" << endl;

        int world[rows][cols];

        cout << rows << " " << cols << endl;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                world[row][col] = 0;
            }
        }

        world[3][2] = 1;
        world[3][3] = 1;
        world[3][4] = 1;
        world[4][3] = 1;

        while (true) {

            int tmp_world[rows][cols];

            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {

                    int neighbors = get_heighbors(world, row, col);

                    if (world[row][col] == 0 && neighbors == 3) {
                        tmp_world[row][col] = 1;
                    } else if (world[row][col] == 1 && (neighbors == 2 || neighbors == 3)) {
                        tmp_world[row][col] = 1;
                    } else {
                        tmp_world[row][col] = 0;
                    }
                }
            }

            for (int row = 0; row < rows; ++row)
                for (int col = 0; col < cols; ++col)
                    world[row][col] = tmp_world[row][col];

            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                    cout << world[row][col] << " ";
                }
                cout << endl;
            }

            cout << endl;

            sleep(1);
        }

        return 0;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

