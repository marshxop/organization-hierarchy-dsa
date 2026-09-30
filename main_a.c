#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_QUEUE 100

typedef struct TreeNode
{
    char name[50];
    struct TreeNode *children[MAX_CHILDREN];
    int childCount;
} TreeNode;


/* Create a new node */
TreeNode* createNode(char name[])
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(node->name, name);
    node->childCount = 0;

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}


/* Add a child to a parent */
void addChild(TreeNode *parent, TreeNode *child)
{
    if (parent->childCount < MAX_CHILDREN)
    {
        parent->children[parent->childCount] = child;
        parent->childCount++;
    }
}


/* Create tree using user input */
void buildTree(TreeNode *node)
{
    int numberOfChildren;
    char childName[50];

    printf("\nEnter number of children for %s: ", node->name);
    scanf("%d", &numberOfChildren);

    if (numberOfChildren > MAX_CHILDREN)
    {
        printf("Maximum %d children allowed.\n", MAX_CHILDREN);
        numberOfChildren = MAX_CHILDREN;
    }

    for (int i = 0; i < numberOfChildren; i++)
    {
        printf("Enter name of child %d of %s: ",
               i + 1, node->name);

        scanf(" %[^\n]", childName);

        TreeNode *child = createNode(childName);

        addChild(node, child);

        /* Recursively create children */
        buildTree(child);
    }
}


/* Level-order traversal */
void levelOrderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;

    TreeNode *queue[MAX_QUEUE];

    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    printf("\nLevel-Order Traversal:\n");

    while (front < rear)
    {
        TreeNode *current = queue[front++];

        printf("%s", current->name);

        if (front < rear || current->childCount > 0)
            printf(" -> ");

        for (int i = 0; i < current->childCount; i++)
        {
            queue[rear++] = current->children[i];
        }
    }

    printf("\n");
}


/* Display hierarchy */
void displayTree(TreeNode *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("|-- %s\n", root->name);

    for (int i = 0; i < root->childCount; i++)
    {
        displayTree(root->children[i], level + 1);
    }
}


/* Calculate tree height */
int treeHeight(TreeNode *root)
{
    if (root == NULL)
        return -1;

    if (root->childCount == 0)
        return 0;

    int maxHeight = -1;

    for (int i = 0; i < root->childCount; i++)
    {
        int height = treeHeight(root->children[i]);

        if (height > maxHeight)
            maxHeight = height;
    }

    return maxHeight + 1;
}


/* Free memory */
void freeTree(TreeNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->childCount; i++)
    {
        freeTree(root->children[i]);
    }

    free(root);
}


int main()
{
    char rootName[50];

    printf("============================================\n");
    printf("ORGANISATIONAL HIERARCHY\n");
    printf("============================================\n");

    /* Get root name */
    printf("\nEnter root of the organisation: ");
    scanf(" %[^\n]", rootName);

    /* Create root */
    TreeNode *root = createNode(rootName);

    /* Build tree */
    printf("\n--- Enter Hierarchy ---\n");

    buildTree(root);

    /* Display hierarchy */
    printf("\n============================================\n");
    printf("ORGANISATIONAL HIERARCHY\n");
    printf("============================================\n");

    printf("%s\n", root->name);

    for (int i = 0; i < root->childCount; i++)
    {
        displayTree(root->children[i], 1);
    }

    /* Level-order traversal */
    printf("\n============================================\n");
    printf("LEVEL-ORDER TRAVERSAL\n");
    printf("============================================\n");

    levelOrderTraversal(root);

    /* Tree height */
    printf("\nTree Height: %d edges\n",
           treeHeight(root));

    /* Free memory */
    freeTree(root);

    return 0;
}
