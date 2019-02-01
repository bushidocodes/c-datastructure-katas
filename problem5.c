#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define MAXV 100

// Write an algorithm that takes a binary tree T(at most N nodes) as an input and computes the number of
// nodes at each depth. The algorithm should store the output in an array D[0:N-1], where your algorithm
// should store the number of nodes at depth k in D[k]

// Input is a binary tree
// Output is an array indexed by level with a value equal to the number of nodes at that level

typedef struct Node
{
    int id;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Stack
{
    Node *data[MAXV];
    int length;
} Stack;

void createNode(Node *this, int id)
{
    this->id = id;
}

void destroyNode(Node *this)
{
    if (this->left != NULL)
    {
        destroyNode(this->left);
    }
    if (this->right != NULL)
    {
        destroyNode(this->right);
    }
    free(this);
}

int calcSizeOfLevel(Node *root, int *levels)
{
    Stack *current, *temp, *next;
    current = malloc(sizeof(Stack));
    current->length = 0;
    next = malloc(sizeof(Stack));
    next->length = 0;
    int depth = 0;

    // add the root to current level
    current->data[current->length] = root;
    current->length++;

    while (current->length > 0)
    {
        if ((current->data[current->length - 1])->left != NULL)
        {
            next->data[next->length] = (current->data[current->length - 1])->left;
            next->length++;
        }
        if ((current->data[current->length - 1])->right != NULL)
        {
            next->data[next->length] = (current->data[current->length - 1])->right;
            next->length++;
        }
        levels[depth]++;

        current->length--;
        //  If the current queue is empty and the next queue has nodes, rotate the queues and reset the next length to 0
        if (current->length == 0 && next->length > 0)
        {
            // Increase Depth
            depth++;
            // Swap queues
            temp = current;
            current = next;
            next = temp;
            next->length = 0;
        }
    }
    free(current);
    free(next);
    return depth;
}

int main(int argc, char *argv[])
{
    int levels[MAXV] = {};
    Node *tree = malloc(sizeof(Node));
    createNode(tree, 0);
    tree->left = malloc(sizeof(Node));
    createNode(tree->left, 1);
    tree->left->left = malloc(sizeof(Node));
    createNode(tree->left->left, 2);
    tree->left->left->left = malloc(sizeof(Node));
    createNode(tree->left->left->left, 3);
    tree->right = malloc(sizeof(Node));
    createNode(tree->right, 4);
    tree->left->right = malloc(sizeof(Node));
    createNode(tree->left->right, 5);
    int depth = calcSizeOfLevel(tree, levels);
    for (int i = 0; i <= depth; i++)
    {
        printf("Level %d has %d nodes\n", i, levels[i]);
    }

    destroyNode(tree);
    return 0;
}