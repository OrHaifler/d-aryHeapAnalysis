#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_SIZE 5000

// Define a structure for a d-ary heap
typedef struct {
    int arr[MAX_SIZE];
    int d;
    int h_size;
} Heap;

// Function to swap two integers
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// Function to view the heap in array representation
void ViewHeap(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to calculate the parent index in a d-ary heap
int Parent(int i, int d) {
    return floor((i - 1) / d);
}

// Function to calculate the left child index in a d-ary heap
int Left(int i, int d) {
    return i * d + 1;
}

// Function to maintain max heap property from a given node
void MaxHeapify(Heap *heap, int i) {
    int l = Left(i, heap->d);
    int largest = i;
    int tmp;

    for (int j = 0; j < heap->d; j++) {
        if (l + j >= heap->h_size)
            break;

        if (heap->arr[l + j] > heap->arr[largest]) {
            largest = l + j;
        }
    }

    if (i != largest) {
        tmp = heap->arr[largest];
        heap->arr[largest] = heap->arr[i];
        heap->arr[i] = tmp;
        MaxHeapify(heap, largest);
    }
}

// Function to build a d-ary heap from an array
Heap BuildHeap(int arr[], int d, int h_size) {
    Heap heap;
    heap.d = d;
    heap.h_size = h_size;

    for (int i = 0; i < h_size; i++) {
        heap.arr[i] = arr[i];
    }

    int leafs = floor((h_size + d - 2) / d);

    for (int i = leafs; i > -1; i--) {
        MaxHeapify(&heap, i);
    }

    return heap;
}

// Function to extract the maximum value from the heap
int ExtractMax(Heap *heap) {
    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->h_size - 1];
    heap->h_size -= 1;
    MaxHeapify(heap, 0);
    return max;
}

// Function to increase the key value at a specific index in the heap
void IncreaseKey(Heap *heap, int i, int key) {
    if (i >= heap->h_size)
        return;

    heap->arr[i] = heap->arr[i] > key ? heap->arr[i] : key;

    while (i > 0 && heap->arr[i] > heap->arr[Parent(i, heap->d)]) {
        swap(&heap->arr[i], &heap->arr[Parent(i, heap->d)]);
        i = Parent(i, heap->d);
    }
}

// Function to insert a new value into the heap
void Insert(Heap *heap, int key) {
    heap->h_size += 1;
    heap->arr[heap->h_size - 1] = INT_MIN;
    IncreaseKey(heap, heap->h_size - 1, key);
}

// Main function to interact with the user and perform heap operations
int main() {
    Heap heap;
    int arr[MAX_SIZE], d, h_size, idx, key, max, action;

    do {
        // Display menu for user actions
        printf("d-ary Heap actions menu:\n");
        printf("1. Build d-ary Heap\n 2. View your heap in an array representation\n 3. Extract the maximum value \n 4. Increase Key in your Heap\n 5. Insert a new value to your Heap\n 6. exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &action);

        switch (action) {
            case 1:
                // Build a d-ary heap based on user input
                printf("Please enter your d value:");
                scanf("%d", &d);
                printf("Please enter your initial heap size:");
                scanf("%d", &h_size);

                if (h_size > MAX_SIZE) {
                    printf("Error: the maximum heap size is %d\n", MAX_SIZE);
                    return 0;
                }

                printf("Please enter your initial %d integers\n", h_size);

                for (int i = 0; i < h_size; i++) {
                    scanf("%d", &arr[i]);
                }

                heap = BuildHeap(arr, d, h_size);
                break;

            case 2:
                // View the heap in array representation
                printf("Your heap, in an array representation, is:\t");
                ViewHeap(heap.arr, heap.h_size);
                break;

            case 3:
                // Extract the maximum value from the heap
                max = ExtractMax(&heap);
                printf("The value that has been extracted: %d\n", max);
                break;

            case 4:
                // Increase the key value at a specific index
                printf("Enter the index to be increased\n");
                scanf("%d", &idx);

                if (idx >= heap.h_size) {
                    printf("Error: invalid index\n");
                    return 0;
                }

                printf("Enter the key\n");
                scanf("%d", &key);
                IncreaseKey(&heap, idx, key);
                break;

            case 5:
                // Insert a new value into the heap
                printf("Please enter your new value\n");
                scanf("%d", &key);
                Insert(&heap, key);
                break;

            case 6:
                // Exit the program
                exit(0);
        }

    } while (1);

    exit(1);
}
