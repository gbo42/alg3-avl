typedef struct tNode{
    struct tNode *p;
    struct tNode *l;
    struct tNode *r;
    int k, h;
} node;

typedef struct tTree{
    struct tNode *root;
} tree;

tree *createTree();
node *createNode(int k);
int nodeHeight(node *n);
void updateHeight(node *n);
void rotateLeft(tree *t, node *x);
void rotateRight(tree *t, node *x);
node *findNode(tree *t, int k);
node *findNodePrint(tree *t, int k);
void insertNode(tree *t, int k);
void deleteNode(tree *t, int k);
void rebalance(tree *t, node *n);
void printTree(tree *t);
void printNode(node *n);
void deleteAll(node *n);
