// assume M and N are the dimensions of the matrix
using namespace std;

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
// and "a" is the array containing the path

// create a new matrix of size NxM
//
#define Line vector<int>
#define Matrix vector<Line>


#define M 7
#define N 5

int lines = M;
int cols = N;
Matrix matrix;
Matrix transposed;

int path[] = {3,3,4,5,5,5,5};

 void printMatrix(Matrix matrix) {
     // Print the new matrix
     cout << "DEBUG: The new matrix is: " << endl;
     for (Line line : matrix) {
         for (int sq : line) {
             cout << sq << " ";
         }
         cout << endl;
     }
 }


void initMatrix(int lines, int cols) {
     for (int i = 0; i < lines; i++) {
         Line newLine(cols, 1);
         matrix.push_back(newLine);
     }

    // Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        /* path.push_back(col_caminho); */
         for (int a = 0; a < col_caminho; a++) {
             matrix[cur_line][a] = 0;
         }
    }
     printMatrix();
}



void transposta() {
     for (int i = 0; i < lines; i++) {
         Line newLine(cols, 1);
         transposed.push_back(newLine);
     }
    // transpose the matrix
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        transposed[j][i] = matrix[i][path[i]];
      }
    }
    
    // reverse the elements in each row of the transposed matrix
    for (int i = 0; i < N; i++) {
      std::reverse(transposed[i], transposed[i] + M);
    }

}
int main () {

    initMatrix(M,N);

    return 0;
}
