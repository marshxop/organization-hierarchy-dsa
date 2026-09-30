#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_QUEUE 50
#define MAX_DEPARTMENTS 20

/* =========================================
   TREE NODE
   ========================================= */

typedef struct TreeNode {
    char name[50];
    struct TreeNode *children[MAX_CHILDREN];
    int childCount;
} TreeNode;


/* =========================================
   CREATE A NEW TREE NODE
   ========================================= */

TreeNode* createNode(const char *name)
{
    TreeNode *node =
        (TreeNode *)malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
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


/* =========================================
   ADD CHILD
   ========================================= */

void addChild(TreeNode *parent, TreeNode *child)
{
    if (parent->childCount < MAX_CHILDREN)
    {
        parent->children[parent->childCount] = child;
        parent->childCount++;
    }
}


/* =========================================
   LEVEL ORDER TRAVERSAL
   ========================================= */

void levelOrderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

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
        {
            printf(" -> ");
        }

        for (int i = 0; i < current->childCount; i++)
        {
            queue[rear++] = current->children[i];
        }
    }

    printf("\n");
}


/* =========================================
   TREE HEIGHT
   ========================================= */

int treeHeight(TreeNode *root)
{
    if (root == NULL)
    {
        return -1;
    }

    if (root->childCount == 0)
    {
        return 0;
    }

    int maxHeight = -1;

    for (int i = 0; i < root->childCount; i++)
    {
        int currentHeight =
            treeHeight(root->children[i]);

        if (currentHeight > maxHeight)
        {
            maxHeight = currentHeight;
        }
    }

    return maxHeight + 1;
}


/* =========================================
   LINEAR SEARCH
   ========================================= */

int linearSearch(
    char departments[][50],
    int n,
    const char *target,
    int *comparisons)
{
    *comparisons = 0;

    for (int i = 0; i < n; i++)
    {
        (*comparisons)++;

        if (strcmp(departments[i], target) == 0)
        {
            return i;
        }
    }

    return -1;
}


/* =========================================
   BINARY SEARCH
   ========================================= */

int binarySearch(
    char departments[][50],
    int n,
    const char *target,
    int *comparisons)
{
    int low = 0;
    int high = n - 1;

    *comparisons = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        (*comparisons)++;

        int result =
            strcmp(departments[mid], target);

        if (result == 0)
        {
            return mid;
        }
        else if (result < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}


/* =========================================
   FREE TREE MEMORY
   ========================================= */

void freeTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < root->childCount; i++)
    {
        freeTree(root->children[i]);
    }

    free(root);
}


/* =========================================
   MAIN FUNCTION
   ========================================= */

int main()
{
    /* =====================================
       PART A - CREATE ORGANISATIONAL TREE
       ===================================== */

    TreeNode *CEO = createNode("CEO");

    TreeNode *HR = createNode("HR");
    TreeNode *Finance = createNode("Finance");
    TreeNode *IT = createNode("IT");

    TreeNode *Development =
        createNode("Development");

    TreeNode *Testing =
        createNode("Testing");

    TreeNode *Frontend =
        createNode("Frontend");

    TreeNode *Backend =
        createNode("Backend");


    /* Build the hierarchy */

    addChild(CEO, HR);
    addChild(CEO, Finance);
    addChild(CEO, IT);

    addChild(IT, Development);
    addChild(IT, Testing);

    addChild(Development, Frontend);
    addChild(Development, Backend);


    /* Display hierarchy */

    printf("============================================\n");
    printf("ORGANISATIONAL HIERARCHY\n");
    printf("============================================\n");

    printf("\n");

    printf("CEO\n");
    printf("|-- HR\n");
    printf("|-- Finance\n");
    printf("|-- IT\n");
    printf("    |-- Development\n");
    printf("        |-- Frontend\n");
    printf("        |-- Backend\n");
    printf("    |-- Testing\n");


    /* Level-order traversal */

    levelOrderTraversal(CEO);


    /* Tree height */

    printf("\nTree Height: %d edges\n",
           treeHeight(CEO));


    /* =====================================
       PART B - DEPARTMENT SEARCH
       ===================================== */

    /*
       Department names must be sorted
       for Binary Search.
    */

    char departments[MAX_DEPARTMENTS][50] =
    {
        "Backend",
        "CEO",
        "Development",
        "Finance",
        "Frontend",
        "HR",
        "IT",
        "Testing"
    };

    int departmentCount = 8;


    printf("\n============================================\n");
    printf("SORTED DEPARTMENT LIST\n");
    printf("============================================\n");

    for (int i = 0;
         i < departmentCount;
         i++)
    {
        printf("%d. %s\n",
               i + 1,
               departments[i]);
    }


    /* Three departments to search */

    const char *searchTargets[] =
    {
        "HR",
        "Development",
        "Testing"
    };


    printf("\n============================================\n");
    printf("SEARCH COMPARISON\n");
    printf("============================================\n");


    for (int i = 0; i < 3; i++)
    {
        int linearComparisons;
        int binaryComparisons;

        int linearResult =
            linearSearch(
                departments,
                departmentCount,
                searchTargets[i],
                &linearComparisons
            );

        int binaryResult =
            binarySearch(
                departments,
                departmentCount,
                searchTargets[i],
                &binaryComparisons
            );


        printf("\nSearch: %s\n",
               searchTargets[i]);


        if (linearResult != -1)
        {
            printf("Linear Search: Found\n");
        }
        else
        {
            printf("Linear Search: Not Found\n");
        }

        printf("Linear Comparisons: %d\n",
               linearComparisons);


        if (binaryResult != -1)
        {
            printf("Binary Search: Found\n");
        }
        else
        {
            printf("Binary Search: Not Found\n");
        }

        printf("Binary Comparisons: %d\n",
               binaryComparisons);
    }


    /* =====================================
       PART C - ANALYSIS
       ===================================== */

    printf("\n============================================\n");
    printf("ANALYSIS\n");
    printf("============================================\n");

    printf("\nTree Height: 3 edges\n");

    printf("\nTraversal Behaviour:\n");
    printf("Level-order traversal visits nodes level by level.\n");
    printf("A queue is used for traversal.\n");

    printf("\nTime Complexity:\n");
    printf("Tree Construction: O(n)\n");
    printf("Level-order Traversal: O(n)\n");
    printf("Height Calculation: O(n)\n");
    printf("Linear Search: O(n)\n");
    printf("Binary Search: O(log n)\n");

    printf("\nSuitability:\n");
    printf("The N-ary tree is suitable for organisational reporting\n");
    printf("because it represents parent-child relationships clearly.\n");

    printf("A sorted array is suitable for department searching\n");
    printf("because Binary Search provides O(log n) time complexity.\n");


    /* Free memory */

    freeTree(CEO);

    return 0;
}