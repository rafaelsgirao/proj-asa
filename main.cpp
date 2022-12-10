using namespace std;
#include <iostream>
#include <vector>

// Constants.
struct square {
    int size;     // Size of square we're building (or have built)
    int cur_line; // Current line
};
typedef struct square Square;

#define Matrix vector<vector<Square *>>
#define uint uint

// define FILLED_SQ 1

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
struct node {
    int line_nr;

    struct node *parent;
    vector<int> prevLine;
    vector<int> line_state;
    // struct node* next;
    vector<struct node *> children;
};

typedef struct node Node;

Node *createNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->parent = NULL;
    return node;
}

// Read matrix size
int readSize(uint &lines, uint &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}

// Calculate the number and the ways of filling a list with edges of the squares

void initAnanas(vector<int> origLine) {
    uint origLineSize = origLine.size();
    vector<int> tmp_line;
    for (int i = 0; i < origLineSize; i++) {
        // Copy vector line but limit size to i
        vector<int> tmp_line(origLine.begin(), origLine.begin() + i);
    }
}
void Ananas(vector<int> line) {
    return; // FIXME implement
}

// Receives a Node, constructs all possible states for that line
void getPossibleStates(Node *node, vector<int> *line) {

    // For every empty square or set of squares, if we can choose placing a
    // square, we can also choose NOT placing said square. for every choice we
    // get, we have to duplicate said vector and call this function again.
    uint prevLineSize = node->prevLine.size();
    uint lineSize = line->size();
    uint max_length = line->size() > node->prevLine.size()
                          ? line->size()
                          : node->prevLine.size();

    // Check for incomplete PartialSquares, fill next line in them
    for (int sq = 0; sq < prevLineSize; sq++) {
        if (0 == 0) {
        }
    };
    return;
}

void auxGetPossibleStates(Node *node, vector<int> *line) {}

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

// Cut off a branch of our tree.
/*
void destroyNode(Node *node) {
    Node *node
    for (Node )
}
*/

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
    for (vector<Square *> line : matrix) {
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
    Node *root = createNode();

    // Get the largest possible square we can fit (given by the diagonal)
    // int result = calculatePossibilities(0, root); //FIXME
    int result = 0;
    cout << "DEBUG: result = " << result;
    return 0;
}