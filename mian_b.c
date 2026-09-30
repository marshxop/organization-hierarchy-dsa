#include <stdio.h>
#include <string.h>

/* Linear Search */
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

/* Binary Search */
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

    for (int i = 0; i < 3; i++)
    {
        int linearComparisons;
        int binaryComparisons;

        linearSearch(
            departments,
            n,
            searchTargets[i],
            &linearComparisons
        );

        binarySearch(
            departments,
            n,
            searchTargets[i],
            &binaryComparisons
        );

        printf("\nSearch: %s\n", searchTargets[i]);

        printf("Linear Search Comparisons: %d\n",
               linearComparisons);

        printf("Binary Search Comparisons: %d\n",
               binaryComparisons);
    }

    return 0;
}
