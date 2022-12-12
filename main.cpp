using namespace std;

#include <algorithm>
#include <iostream>
#include <vector>
#include "main.h"

// Global variables.
int largest_square = 0;
vector<int> path;
Matrix matrix;
uint numberOfCases =0;



// Read matrix size
int readSize(uint &lines, uint &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}




Matrix initMatrix(int lines, uint cols) {
    // Create a matrix of size lines x cols, initialized w/ empty squares
    // https://stackoverflow.com/questions/65646403/initialization-of-vector-of-vectors
    Matrix matrix(lines, vector<int>(cols, 1));

    // Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        path.push_back(col_caminho);
        for (int a = 0; a < col_caminho; a++) {
            matrix[cur_line][a] = 0;
        }
    }
    // Print the new matrix
    cout << "DEBUG: The new matrix is: " << endl;
    for (Line line : matrix) {
        for (int sq : line) {
            cout << sq << " ";
        }
        cout << endl;
    }
    return matrix;
}

void removeSquare(int l,int c,int size){
    for(int i=0;i<size;i++){
        matrix[l][c+i]=0;
        matrix[l+i][c]=0;
    }
    

    return;
}

int main() {
    uint lines;
    uint cols;

    // Read size of matrix dimensions
    readSize(lines, cols);


    // Create matrix
    Matrix matrix = initMatrix(lines, cols);

    return 0;
}