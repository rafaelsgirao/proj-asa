using namespace std;
#include <iostream>
#include <vector>
#include "main.h"

// Global variables.
int largest_square = 0;
vector<int> path;
Matrix matrix;

// A partial square is a structure as a sort of promise that we're building a
// square in that place.
//  E.g a PartialSquare could be a 3x3 square, then size = 3 and curl_line would
//  be either 1, 2 or 3

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
    getPossibleStates(node, &curLine);

    for (Node *child : node->children) {
        makeTree(child);
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
    getPossibleStates(root, &line);
    // int result = calculatePossibilities(0, root); //FIXME
    int result = 0;
    cout << "DEBUG: result = " << result;
    return 0;
}