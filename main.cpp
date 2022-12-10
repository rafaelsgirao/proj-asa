using namespace std;
#include <iostream>
#include <vector>

#define EMPTY_SQ 0
#define INVALID_SQ 1
#define Matrix vector<vector<int>>
#define uint uint

// define FILLED_SQ 1
// Global variables

int largest_square = 0;
vector<int> path;

Matrix matrix;

// Read matrix size
int readSize(uint &lines, uint &cols) {
    cin >> lines;
    cin >> cols;
    return 0;
}

// A partial square is a structure as a sort of promise that we're building a
// square in that place.
//  E.g a PartialSquare could be a 3x3 square, then size = 3 and curl_line would
//  be either 1, 2 or 3.
struct PartialSquare {
    int size;
    int curl_line;
};

typedef struct PartialSquare PSq;
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
// typedef struct node* link;

// Add edge
void addEdge(Matrix adj, int parent, int son) {
    adj[parent].push_back(son);
    adj[son].push_back(parent);
}

// Calculate the number and the ways of filling a list with edges of the squares

// void calculatePossibilities(int line, Matrix adj,int
// biggestSquare,vector<int> matrixLine){
int calculatePossibilities(int cur_line_nr, Node *node) {

    /*
        for(unsigned long int i=0;i < sizeof(matrix[cur_line_nr]);i++){
            vector<int> list(path[i],0);
            node->linha=list;
            node->curr_lin=cur_line_nr;
            initAnanas(node);
            vector<Node *> children;
            for(Node j: node->children){
                calculatePossibilities(cur_line_nr+1, node->children);
            }
            break;
        }
    */

    return 0; // FIXME return actual value
}

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
            return; // FIXME
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
    while (matrix[line][col] == 0) {
        // Go to next upper right square (diagonal) and see if it's still free
        line--;
        col++;
        largest_square++;
    }
    printf("DEBUG: Largest square is %d\n", largest_square);
    return largest_square;
}

Node *createNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->parent = NULL;
    return node;
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
    Matrix matrix(lines, vector<int>(cols, INVALID_SQ));

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
    for (vector<int> line : matrix) {
        for (int col : line) {
            cout << col << " ";
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

    // Create root of our possibilities (which corresponds to first line)
    Node *root = createNode();

    // Get the largest possible square we can fit (given by the diagonal)
    int result = calculatePossibilities(0, root);

    cout << "DEBUG: result = " << result;
    return 0;
}