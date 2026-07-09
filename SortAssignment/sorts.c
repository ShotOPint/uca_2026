#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//------------------------------------------------------------
// Array Generators
//------------------------------------------------------------

// Generates a random array
int* generateRandomArray(int size)
{
    int *arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100000;

    return arr;
}

// Generates an ascending array
int* generateAscendingArray(int size)
{
    int *arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        arr[i] = i;

    return arr;
}

// Generates a descending array
int* generateDescendingArray(int size)
{
    int *arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        arr[i] = size - i;

    return arr;
}

//------------------------------------------------------------
// Utility Functions
//------------------------------------------------------------

// Creates a copy of an array
int* copyArray(int source[], int size)
{
    int *copy = (int*)malloc(size * sizeof(int));

    if (copy == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    memcpy(copy, source, size * sizeof(int));

    return copy;
}

// Checks whether an array is sorted
bool isSorted(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }

    return true;
}

// Swaps two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//------------------------------------------------------------
// Bubble Sort
//------------------------------------------------------------

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // Stop if already sorted
        if (!swapped)
            break;
    }
}

//------------------------------------------------------------
// Insertion Sort
//------------------------------------------------------------

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

//------------------------------------------------------------
// Selection Sort
//------------------------------------------------------------

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
            swap(&arr[i], &arr[minIndex]);
    }
}
//------------------------------------------------------------
// Quick Sort
//------------------------------------------------------------

int partition(int arr[], int low, int high)
{
    // Middle element as pivot (better than always using last element)
    int mid = low + (high - low) / 2;
    swap(&arr[mid], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Wrapper
void quickSortWrapper(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}


//------------------------------------------------------------
// Merge Sort
//------------------------------------------------------------

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Wrapper
void mergeSortWrapper(int arr[], int n)
{
    mergeSort(arr, 0, n - 1);
}


//------------------------------------------------------------
// Heap Sort
//------------------------------------------------------------

void heapify(int arr[], int n, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root)
    {
        swap(&arr[root], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}
//------------------------------------------------------------
// Benchmark Function
//------------------------------------------------------------

double benchmark(void (*sortFunc)(int[], int), int original[], int size)
{
    int *arr = copyArray(original, size);

    clock_t start = clock();

    sortFunc(arr, size);

    clock_t end = clock();

    if (!isSorted(arr, size))
    {
        printf("Sorting Failed!\n");
    }

    free(arr);

    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}


//------------------------------------------------------------
// Benchmark Helper
//------------------------------------------------------------

void testAllSorts(int arr[], int size, const char *type)
{
    printf("\n%s Input\n", type);
    printf("----------------------------------------\n");

    printf("Bubble Sort     : %.3f ms\n",
           benchmark(bubbleSort, arr, size));

    printf("Insertion Sort  : %.3f ms\n",
           benchmark(insertionSort, arr, size));

    printf("Selection Sort  : %.3f ms\n",
           benchmark(selectionSort, arr, size));

    printf("Merge Sort      : %.3f ms\n",
           benchmark(mergeSortWrapper, arr, size));

    printf("Quick Sort      : %.3f ms\n",
           benchmark(quickSortWrapper, arr, size));

    printf("Heap Sort       : %.3f ms\n",
           benchmark(heapSort, arr, size));
}


//------------------------------------------------------------
// Main Function
//------------------------------------------------------------

int main()
{
    srand((unsigned)time(NULL));

    int sizes[] =
    {
        8000,
        12000,
        16000,
        20000,
        24000,
        28000,
        32000,
        36000
    };

    int totalSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < totalSizes; i++)
    {
        int n = sizes[i];

        printf("\n====================================================\n");
        printf("Array Size : %d\n", n);
        printf("====================================================\n");

        // ---------------- Random ----------------

        int *randomArray = generateRandomArray(n);

        testAllSorts(randomArray, n, "Random");

        free(randomArray);


        // ---------------- Ascending ----------------

        int *ascendingArray = generateAscendingArray(n);

        testAllSorts(ascendingArray, n, "Ascending");

        free(ascendingArray);


        // ---------------- Descending ----------------

        int *descendingArray = generateDescendingArray(n);

        testAllSorts(descendingArray, n, "Descending");

        free(descendingArray);
    }

    return 0;
}
