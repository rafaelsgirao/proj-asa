using namespace std;

#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include "main.h"

// Global variables.
int largest_square = 0;
vector<int> path;
Matrix matrix;

// A partial square is a structure as a sort of promise that we're building a
// square in that place.
//  E.g a PartialSquare could be a 3x3 square, then size = 3 and curl_line would
//  be either 1, 2 or 3

// Square utils.
Square createSquare(uint size, uint cur_line) {
    Square sq = {size, cur_line};
    return sq;
}

Square INVALID_SQ = {-1, -1}; // A square where we can't ladrilhate
Square EMPTY_SQ = {0, 0};

/*
A node is a struct that holds
- the current line number
- A pointer to the parent node
- A vector, containing the previous line's arrangements
- A vector of children nodes, containing all possible states of line #cur_line

Special cases:
- First line (top most) is represented by a root node whose prevLine is line 0's
initial state, line_nr = 0 and whose children are all possible states for line 0
itself

*/

Node *createNode(uint line_nr) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->parent = NULL;
    node->line_nr = line_nr;
    return node;
}

// Read matrix size
int readSize(uint &lines, uint &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}

// On each iteration, we look at the node's prevLine, get the corresponding line
// on the matrix and see what it's most empty state can be.
void makeTree(Node *node) {
    // If size = matrix size +1, we quit (in other words, if prevLine is the
    // last line)
    if (node->line_nr + 1 == matrix.size()) {
        return;
    }
    Line curLine = matrix[node->line_nr];
    Line prevLine = node->prevLine;
    uint max_length =
        curLine.size() > prevLine.size() ? curLine.size() : prevLine.size();

    uint sq_i = 0;
    uint prevLineSize = prevLine.size();

    // Make up the initial state of the line, given previous line's state
    // Fill current line with requirements from previous line (i.e
    // continue/finish incomplete squares)
    while (sq_i < prevLineSize) {
        // Check if there's a square at current pointer in previous line
        if (prevLine[sq_i] != &EMPTY_SQ && prevLine[sq_i] != &INVALID_SQ) {
            // If so, is it unfinished?
            Square prevSquare = *prevLine[sq_i];
            if (prevSquare.size == prevSquare.cur_line) {
                // Square we saw is finished, move to first square after it
                sq_i += prevSquare.size; // Skip whole square
                continue;
            } else {
                // Square we saw isn't finished - build next line!
                Square newSquareLine =
                    createSquare(prevSquare.size, prevSquare.cur_line + 1);
                for (int i = 0; i < prevSquare.size; i++) {
                    curLine[sq_i] = &newSquareLine;
                    sq_i++;
                }
                continue; // Skip newly created block
            }
        }
        sq_i++;
    }
    // Now that we have a line with hard requirements from prevLine, we can
    // build all possible states

    //getPossibleStates(node, curLine);

    for (Node *child : node->children) {
        makeTree(child);
    }
    return;
}

// Memory Programming

//vector<vector<int>> dp;
long long int dp[100][100];

// Funçao que susbititui o push_back no vector
void add(int line,long long int number){
    for(int i=0;i<sizeof(dp[line][0]);i++){
        if(dp[line][i]==0){
            dp[line][i]=number;
            return;
        } 
    }
    return;
}
// Memory Programming
int calcLineOfNumber(long long int id) {
    int line = 0;
    while(id!=0) {
        line++;
        id=id/10;
    }
    return line;
}

int calcNumberToAdd(int squareLength) {
    int times = squareLength;
    int lengthNumber= calcLineOfNumber(squareLength);
    int result = 0;
    for (times; times > 0; times--) {
        
        result = result * pow(10,lengthNumber) + squareLength;
    }
    return result;
}



bool idInCache(long long int count) {
    long long int lineOfId = calcLineOfNumber(count);
    

    for(int i=0;i<sizeof(dp[lineOfId]);i++){
        if(dp[lineOfId][i]==0)
            return false;
        if(dp[lineOfId][i]==count)
            return true;
    }
    //if (find(dp[lineOfId].begin(), dp[lineOfId].end(), count) !=
      //  dp[lineOfId].back()) {
    return false;
}


/*

*/
int f(int curr_cols, int count,long long int solution) {
    if (curr_cols > count) {
        return 0;
    }

    for (int square_length = 1; square_length <= count; square_length++) {
        solution =
            solution * pow(10,square_length) + calcNumberToAdd(square_length);
        //Square squareToAdd= createSquare(square_length,0); //NEW
        
        if (idInCache(solution) == true) {
            cout<< solution << endl;
            cout<< "OLE" << endl;
            f(curr_cols+square_length,count,solution);
            continue;
        }
        if ((square_length + curr_cols > count)) {
            return 1;
        }
        cout<<solution<< endl;
        //dp[curr_cols+square_length].push_back(solution);
        add(curr_cols+square_length,solution);

        f(curr_cols + square_length, count,solution);
        solution=solution / pow(10,square_length);
    }
    return 0;
}

// Receives a Node, constructs all possible states for that line
 void getPossibleStates(
    Node *node, Line line) { // TODO: is line a copy or passed by reference?

    // For every empty square or set of squares, if we can choose placing a
    // square, we can also choose NOT placing said square. for every choice we
    // get, we have to duplicate said vector and call this function again.
    // To check, but I think that our end result will be the number of times we
    // branch out.
    uint prevLineSize = node->prevLine.size();
    uint lineSize = line.size();
    uint max_length = line.size() > node->prevLine.size()
                          ? line.size()
                          : node->prevLine.size();

    // Check for incomplete PartialSquares, fill next line in them
    uint sq_i = 0;
    uint count = 0;
    // The secret sauce.
    while (sq_i < lineSize) {
        Square *val = line[sq_i];
        // Attempt to see what's the largest square we can place
        if (val == &EMPTY_SQ) {
            count++;
            sq_i++;
            continue;
        }
        // We've reached an invalid square. Can we build squares where we saw an
        // empty spot??
        if (count == 0) {
            // No, we can't.
            sq_i++;
            continue;
        }
        if (count == 1) {
            Square newSquare = createSquare(1, 1);
            line[sq_i] = &newSquare;
            sq_i++;
            continue;
        }
        // Yes, we can! Fork our path
        if (count > 1 && val->size > 1) {
            f(1, count,0);
        }
    }

    /*
    for (int sq_i = 0; sq_i < lineSize; sq_i++) {
        for
        //Note for future self:
        TODO HERE
          Iterate through line, find all squares of all sizes we can place in
    here. For every square we can place, we're going to branch into two
    possibilities: We're NOT going to place the square on one on the branches,
    and we're going to on the other. We're going to end up with two copies of
    Line - one where we put the square and continue To avoid an infinite
    recursion, we mark the branch line where we don't WANT to place a square
    there as invalid squares.

    }
    */
}

// Receives a line and a position in the line.
//  Places a new square of size square_size, starting at sq_start_pos.
void placeNewSquare(Line *lineptr, uint square_size, uint sq_start_pos) {
    Line line = *lineptr;
    Square newSquare = createSquare(square_size, 1);
    for (int i = 0; i < square_size; i++) {
        line[sq_start_pos] = &newSquare;
    }
    return;
}

void auxGetPossibleStates(Node *node, Line *line) {}

// Calculate largest square that can fit inside the path
int getLargestSquare(Matrix matrix) {
    uint line = matrix.size() - 1;
    uint col = 0;
    printf("Line %d, col %d\n", line, col);
    while (matrix[line][col] == &EMPTY_SQ) {
        // Go to next upper right square (diagonal) and see if it's still free
        line--;
        col++;
        largest_square++;
    }
    printf("DEBUG: Largest square is %d\n", largest_square);
    return largest_square;
}

Matrix initMatrix(uint lines, uint cols) {
    // Create a matrix of size lines x cols, initialized w/ empty squares
    // https://stackoverflow.com/questions/65646403/initialization-of-vector-of-vectors
    Matrix matrix(lines, vector<Square *>(cols, &INVALID_SQ));

    // Loop through columns
    int col_caminho = 0;
    for (int cur_line = 0; cur_line < lines; cur_line++) {

        cin >> col_caminho;
        path.push_back(col_caminho);
        for (int a = 0; a < col_caminho; a++) {
            matrix[cur_line][a] = &EMPTY_SQ;
        }
    }
    // Print the new matrix
    cout << "DEBUG: The new matrix is: " << endl;
    for (Line line : matrix) {
        for (Square *sq : line) {
            cout << sq->size << "    ";
        }
        cout << endl;
    }
    return matrix;
}

int main() {
    uint lines;
    uint cols;
    
    // Read size of matrix dimensions
    readSize(lines, cols);
    
    // Create matrix
    Matrix matrix = initMatrix(lines, cols);

    // Get largest square. Will be dumped to global variable.
    getLargestSquare(matrix);

    // Create root of our possibilities (which corresponds to first line)
    Node *root = createNode(0);

    // Get the largest possible square we can fit (given by the diagonal)
    Line line = matrix[0];
    root->prevLine = line;

    //getPossibleStates(root, line);        
    
    // int result = calculatePossibilities(0, root); //FIXME
    int result = 0;
    cout << "DEBUG: result = " << result << endl;
    
    f(0, cols,0);
    cout << dp[3][1] << endl;
    
    return 0;
}
