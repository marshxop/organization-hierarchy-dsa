# Organisational Hierarchy using Tree and Searching Algorithms

## Data Structures and Algorithms Assignment

### Problem Statement

A company has the following organisational hierarchy:

```text
CEO
├── HR
├── Finance
└── IT
    ├── Development
    │   ├── Frontend
    │   └── Backend
    └── Testing
```

### Questions

**a)** Represent the hierarchy using a suitable tree structure and implement its construction. Execute the program and display the hierarchy using level-order traversal.

**b)** Store the department names in a suitable searchable representation and compare Linear Search and Binary Search for locating a department. Record the number of comparisons for at least three searches.

**c)** Analyse:
- Tree height
- Traversal behaviour
- Search comparisons
- Time complexity of the selected operations

Determine whether the chosen representation is suitable for organisational reporting and department searching.

---

# (a) Tree Representation and Level-Order Traversal

## Suitable Data Structure

An **N-ary tree** is used because a node can have multiple children.

The hierarchy is represented as:

```text
                 CEO
              /   |    \
            HR  Finance  IT
                       /    \
                Development  Testing
                  /      \
             Frontend    Backend
```

The program accepts the tree structure as **user input**. For every department, the user enters the number of children and their names.

## C Program

```c
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
        node->children[i] = NULL;

    return node;
}

void addChild(TreeNode *parent, TreeNode *child)
{
    if (parent->childCount < MAX_CHILDREN)
    {
        parent->children[parent->childCount] = child;
        parent->childCount++;
    }
}

void buildTree(TreeNode *node)
{
    int numberOfChildren;
    char childName[50];

    printf("\nEnter number of children for %s: ", node->name);
    scanf("%d", &numberOfChildren);

    if (numberOfChildren > MAX_CHILDREN)
        numberOfChildren = MAX_CHILDREN;

    for (int i = 0; i < numberOfChildren; i++)
    {
        printf("Enter name of child %d of %s: ",
               i + 1, node->name);

        scanf(" %[^\n]", childName);

        TreeNode *child = createNode(childName);
        addChild(node, child);

        buildTree(child);
    }
}

void levelOrderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;

    TreeNode *queue[MAX_QUEUE];
    int front = 0, rear = 0;

    queue[rear++] = root;

    printf("\nLevel-Order Traversal:\n");

    while (front < rear)
    {
        TreeNode *current = queue[front++];

        printf("%s", current->name);

        if (front < rear || current->childCount > 0)
            printf(" -> ");

        for (int i = 0; i < current->childCount; i++)
            queue[rear++] = current->children[i];
    }

    printf("\n");
}

void displayTree(TreeNode *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("|-- %s\n", root->name);

    for (int i = 0; i < root->childCount; i++)
        displayTree(root->children[i], level + 1);
}

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

void freeTree(TreeNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->childCount; i++)
        freeTree(root->children[i]);

    free(root);
}

int main()
{
    char rootName[50];

    printf("============================================\n");
    printf("ORGANISATIONAL HIERARCHY\n");
    printf("============================================\n");

    printf("\nEnter root of the organisation: ");
    scanf(" %[^\n]", rootName);

    TreeNode *root = createNode(rootName);

    printf("\n--- Enter Hierarchy ---\n");
    buildTree(root);

    printf("\n============================================\n");
    printf("ORGANISATIONAL HIERARCHY\n");
    printf("============================================\n");

    printf("%s\n", root->name);

    for (int i = 0; i < root->childCount; i++)
        displayTree(root->children[i], 1);

    printf("\n============================================\n");
    printf("LEVEL-ORDER TRAVERSAL\n");
    printf("============================================\n");

    levelOrderTraversal(root);

    printf("\nTree Height: %d edges\n", treeHeight(root));

    freeTree(root);

    return 0;
}
```

## Sample Input

```text
Enter root of the organisation: CEO

Enter number of children for CEO: 3
Enter name of child 1 of CEO: HR
Enter number of children for HR: 0
Enter name of child 2 of CEO: Finance
Enter number of children for Finance: 0
Enter name of child 3 of CEO: IT
Enter number of children for IT: 2
Enter name of child 1 of IT: Development
Enter number of children for Development: 2
Enter name of child 1 of Development: Frontend
Enter number of children for Frontend: 0
Enter name of child 2 of Development: Backend
Enter number of children for Backend: 0
Enter name of child 2 of IT: Testing
Enter number of children for Testing: 0
```

## Sample Output

```text
ORGANISATIONAL HIERARCHY

CEO
    |-- HR
    |-- Finance
    |-- IT
        |-- Development
            |-- Frontend
            |-- Backend
        |-- Testing

LEVEL-ORDER TRAVERSAL

CEO -> HR -> Finance -> IT -> Development -> Testing -> Frontend -> Backend

Tree Height: 3 edges
```

## Result for (a)

The organisational hierarchy was successfully represented using an N-ary tree. The program accepts the hierarchy from the user and displays it using level-order traversal.

---

# (b) Linear Search and Binary Search

## Search Representation

The department names are stored in a **sorted array**:

```text
Backend
CEO
Development
Finance
Frontend
HR
IT
Testing
```

A sorted array is necessary for Binary Search.

## C Program

```c
#include <stdio.h>
#include <string.h>

int linearSearch(char departments[][50], int n,
                 const char *target, int *comparisons)
{
    *comparisons = 0;

    for (int i = 0; i < n; i++)
    {
        (*comparisons)++;

        if (strcmp(departments[i], target) == 0)
            return i;
    }

    return -1;
}

int binarySearch(char departments[][50], int n,
                 const char *target, int *comparisons)
{
    int low = 0;
    int high = n - 1;

    *comparisons = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        (*comparisons)++;

        int result = strcmp(departments[mid], target);

        if (result == 0)
            return mid;
        else if (result < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    char departments[8][50] =
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

    const char *searchTargets[] =
    {
        "HR",
        "Development",
        "Testing"
    };

    int n = 8;

    printf("Sorted Department List:\n");

    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, departments[i]);

    printf("\nSearch Comparison:\n");

    for (int i = 0; i < 3; i++)
    {
        int linearComparisons;
        int binaryComparisons;

        linearSearch(departments, n,
                     searchTargets[i],
                     &linearComparisons);

        binarySearch(departments, n,
                     searchTargets[i],
                     &binaryComparisons);

        printf("\nSearch: %s\n", searchTargets[i]);
        printf("Linear Search Comparisons: %d\n",
               linearComparisons);
        printf("Binary Search Comparisons: %d\n",
               binaryComparisons);
    }

    return 0;
}
```

## Output

```text
Search: HR
Linear Search Comparisons: 6
Binary Search Comparisons: 2

Search: Development
Linear Search Comparisons: 3
Binary Search Comparisons: 3

Search: Testing
Linear Search Comparisons: 8
Binary Search Comparisons: 4
```

## Comparison Table

| Department | Linear Search | Binary Search |
|---|---:|---:|
| HR | 6 | 2 |
| Development | 3 | 3 |
| Testing | 8 | 4 |

## Result for (b)

Binary Search uses fewer comparisons for HR and Testing in this example. Development requires three comparisons in both methods because of its position in the sorted array.

Binary Search requires sorted data, but its time complexity is better for larger datasets.

---

# (c) Analysis

## 1. Tree Height

The longest path is:

```text
CEO → IT → Development → Frontend
```

or

```text
CEO → IT → Development → Backend
```

There are three edges.

**Tree Height = 3**

---

## 2. Traversal Behaviour

Level-order traversal visits nodes level by level.

```text
Level 0: CEO
Level 1: HR, Finance, IT
Level 2: Development, Testing
Level 3: Frontend, Backend
```

Traversal order:

```text
CEO → HR → Finance → IT → Development → Testing → Frontend → Backend
```

A queue is used to maintain the correct order.

---

## 3. Search Comparisons

| Department | Linear Search | Binary Search |
|---|---:|---:|
| HR | 6 | 2 |
| Development | 3 | 3 |
| Testing | 8 | 4 |

The number of comparisons depends on the position of the department. Binary Search reduces the search range by half at every step.

---

## 4. Time Complexity

| Operation | Time Complexity |
|---|---|
| Tree Construction | O(n) |
| Level-Order Traversal | O(n) |
| Height Calculation | O(n) |
| Linear Search | O(n) |
| Binary Search | O(log n) |

### Explanation

- **Tree Construction:** Each node/relationship is created once.
- **Level-Order Traversal:** Every node is visited once.
- **Height Calculation:** Every node may be examined.
- **Linear Search:** Elements may be checked one by one.
- **Binary Search:** The search range is approximately halved at each step.

---

## 5. Suitability for Organisational Reporting

The N-ary tree is suitable for organisational reporting because it naturally represents parent-child relationships.

For example:

```text
CEO
└── IT
    └── Development
        ├── Frontend
        └── Backend
```

This makes the hierarchy easy to display and understand.

## 6. Suitability for Department Searching

A sorted array is suitable for searching department names because it supports Binary Search.

```text
Linear Search  → O(n)
Binary Search  → O(log n)
```

Therefore, Binary Search is efficient when the department list is sorted.

A limitation is that maintaining sorted order after frequent insertions may require additional work.

## Final Conclusion

The combination of an **N-ary tree, queue, and sorted array** is suitable for the given problem.

The N-ary tree represents the organisational structure, the queue supports level-order traversal, and the sorted array supports efficient department searching using Binary Search.

---

# How to Run

1. Open an online C compiler such as OnlineGDB, Programiz, or OneCompiler.
2. Copy the program for **(a)** into the compiler.
3. Run it and enter the organisational hierarchy.
4. Copy the output into your `output.txt` file if required.
5. Run the program for **(b)** separately.
6. Upload the programs and README to GitHub.

## Suggested GitHub Structure

```text
organization-hierarchy-dsa/
│
├── main.c
├── search.c
├── output.txt
└── README.md
```

## Technologies Used

- Language: C
- Data Structure: N-ary Tree
- Traversal: Level-Order Traversal
- Auxiliary Structure: Queue
- Searching: Linear Search and Binary Search
- Search Storage: Sorted Array
