using namespace std;

#include "main.h"
#include <algorithm>
#include <iostream>
#include <vector>

vector<int> path;
uint numberOfCases = 0;

Matrix matrix;

// Read matrix size
int readSize(uint &lines, uint &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}

void printMatrix() {
    // Print the new matrix
    cout << "DEBUG: The new matrix is: " << endl;
    for (Line line : matrix) {
        for (int sq : line) {
            cout << sq << " ";
        }
        cout << endl;
    }
}

void initMatrix(int lines, uint cols) {
    for (int i = 0; i < lines; i++) {
        Line newLine(cols, 1);
        matrix.push_back(newLine);
    }

    // Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        path.push_back(col_caminho);
        for (int a = 0; a < col_caminho; a++) {
            matrix[cur_line][a] = 0;
        }
    }
    printMatrix();
}

void setSquare(int l, int c, int size, int color) {
    for (int i = l; i < l + size; i++) {
        for (int j = c; j < c + size; j++) {
            matrix[i].at(j) = 1;
        }
    }
    return;
}

void addSquare(int l, int c, int size) { setSquare(l, c, size, 1); }
void delSquare(int l, int c, int size) { setSquare(l, c, size, 0); }

bool canAddSquare(int line, int cols, int size) {
    for (int i = line; i < size + line; i++) {
        for (int j = cols; j < size + cols; j++) {
            if (matrix[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

// f(0, 0, 1)

int f(int line, int col, int size) {
    int rslt = 0;
    while (rslt == 0) {
        if (canAddSquare(line, col, size)) {
            addSquare(line, col, size);
            f(line + size, col + size, size);
        }
    }

    return rslt;
}

void calculatePossibilities(int c, int l) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j++; j++) {
            if (matrix[i][j] == 0) {
                setSquare(i, j, 1, 1);
            }
        }
    }
    return;
}
int main() {
    uint lines;
    uint cols;

    // Read size of matrix dimensions
    readSize(lines, cols);

    // Create matrix
    initMatrix(lines, cols);
    printMatrix();
    f(0, 0, 1);
    cout << canAddSquare(0, 0, 1);
    return 0;
}