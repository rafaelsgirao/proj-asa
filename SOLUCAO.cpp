using namespace std;

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

#define Line vector<int>
#define Matrix vector<Line>

vector<int> path;
unordered_map< long long unsigned int, unsigned long int > cache;
int lines;
int cols;

Matrix matrix;

long long unsigned int hashVector(vector<int> path){
    long long unsigned int res=1;
    for(long unsigned int i=1;i<path.capacity();i++){
        res*= (res+17)^path[i]^(path[i]*1149);
    }
    //cout << res << endl;
    return res;
}

// void printPath(vector<int> path){
//     for (long unsigned int i=0;i<path.capacity();i++)
//         cout << path[i] << " , ";
//     cout << endl;
// }

// Read matrix size
int readSize(int &lines, int &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}

// void printMatrix() {
//     // Print the new matrix
//     cout << "DEBUG: The new matrix is: " << endl;
//     for (Line line : matrix) {
//         for (int sq : line) {
//             cout << sq << " ";
//         }
//         cout << endl;
//     }
// }

void initMatrix(int lines, int cols) {
    // for (int i = 0; i < lines; i++) {
    //     Line newLine(cols, 1);
    //     matrix.push_back(newLine);
    // }

    // Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        path.push_back(col_caminho);
        // for (int a = 0; a < col_caminho; a++) {
        //     matrix[cur_line][a] = 0;
        // }
    }
    //printMatrix();
}

// f(0, 0, 1)
vector<int> findFirstEmptySquare(vector<int> path){
    vector<int> coord={0,0};
    for(long unsigned int j=0;j<path.capacity();j++){
        if(path[j]-1>coord[0]){
            coord[0]=path[j]-1;
            coord[1]=j;
        }
    }
    return coord;
}

int findLargestSquare(vector<int> coord,vector<int> path){
    int x=coord[0]; 
    int y=coord[1];
    if(x==0 && y==0){
        return 0;
    }
    int result=1;
    bool go=true;
    while(go){
        y++;
        x--;
        if(y>lines || x<0){
            break;
        }
        if(path[y]-1<coord[0]){
            break;
        }
        if(path[y]-1==coord[0]){
            result++;
        }
    }
    return result;
}

int findWhereIsTheSquare(vector<int> coord){
    //cout << "COLUNA : " << coord[0] << " ; LINHA: " <<coord[1] << endl;
    return coord[1];
}

unsigned long int f(vector<int> vector){
    long long unsigned int hashed_value= hashVector(vector);
    unsigned long int res=0;
    int largestSquare;
    int locationOfSquare;
    //FIX ME
    //Dynamic Programming 
    if(cache.count(hashed_value)){
        return cache[hashed_value];
        //return the value of the cache associated with vector
    }

    locationOfSquare=findWhereIsTheSquare(findFirstEmptySquare(vector));
    largestSquare=findLargestSquare(findFirstEmptySquare(vector),vector);
    if(largestSquare==0){
        return 0;
    }
    for(int i=1;i<=largestSquare;i++){
        int j=0;
        while(j<i){
            vector[locationOfSquare+j]=vector[locationOfSquare+j]-i;
            j++;
        }
        j--;
        if(i>1)
        res+=f(vector)+1;
        else
        res+=f(vector);
        while(j>=0){
            vector[locationOfSquare+j]=vector[locationOfSquare+j]+i;
            j--;
        }
        
    }
    // add value and vector to cache
    cache[hashed_value]=res;
    return res;
    
}

bool pathZero(vector<int> path){
    for(unsigned long int i=0;i<path.capacity();i++){
        if(path[i]!=0){
            return false;
        }
    }
    return true;
}

int main() {
    
    // Read size of matrix dimensions
    readSize(lines, cols);

    // Create matrix
    initMatrix(lines, cols);
    if(pathZero(path)|| lines==0 || cols==0){
        cout << 0 << endl;
        return 0;
    }
    cout << f(path)+1 << endl;
    return 0;
}
