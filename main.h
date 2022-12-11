#define Line vector<Square *>
#define Matrix vector<Line>

#define uint uint


// Structs.
struct square {
    int size;     // Size of square we're building (or have built)
    int cur_line; // Current line
};
typedef struct square Square;

struct node {
    uint line_nr;
    struct node *parent;
    Line prevLine;
    vector<struct node *> children;
};

typedef struct node Node;

// Function definitions.

void getPossibleStates(Node *node, Line *lineptr);

