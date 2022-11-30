using namespace std;
#include <iostream>

//Read matrix size
int readSize(int &lines, int &cols)
{
    cin >> lines;
    cin >> cols;
    return 0;
}

int main() {
    int lines;
    int cols;
    readSize(lines,cols);
    int matrix[lines][cols] = {0};
    cout << "The matrix is: " << endl;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 1;
        }
    }
    //Print the matrix
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    //Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        for(int a=0; a < col_caminho; a++){
            matrix[cur_line][a]=0;

        }
    }
    //Print the new matrix
    cout << "The new matrix is: " << endl;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}