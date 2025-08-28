#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void swap(int *p, int *q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void bubble_sort(int arr[], int n){

    for(int i=0; i<n-1; i++){
        int is_swap = 0;
        for(int j=0; j<n-i-1; j++){
            if(arr[j]> arr[j+1]){
                swap(&arr[j],&arr[j+1]);
                is_swap = 1;
            }
        }
        if(!is_swap){
            return;
        }
    }
}

void selection_sort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        int si=i;
        for(int j=i+1; j<n; j++){
            if(arr[si]>arr[j]){
                si=j;
            }
        }
        swap(&arr[si], &arr[i]);
    }
}

void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) { 
        for (int i = gap; i < n; i++) {
            int j = i;
            while (j - gap >= 0 && arr[j - gap] > arr[j]) {
                swap(&arr[j], &arr[j - gap]);
                j -= gap;
            }
        }
    }
}

void insertion_sort(int arr[], int n){
    for(int i=1;i<n;i++){
        int curr = arr[i];
        int prev = i-1;
        while(prev>=0 && arr[prev]>curr){
            arr[prev+1] = arr[prev];
            prev--;
        }
        arr[prev+1] = curr;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;        

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   
    int n2 = right - mid;      

    int L[n1], R[n2];          

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;          
    int left = 2 * i + 1;     
    int right = 2 * i + 2;    

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countingSort(int arr[], int n, int exp) {
    int output[n]; 
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix_sort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

void counting_sort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int count[max + 1];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    int output[n];
    for (int i = n - 1; i >= 0; i--) {  
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void insert_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort for integers
void bucket_sort(int arr[], int n, int bucket_size) {
    if (n <= 0) return;

    // Step 1: Find min and max
    int min_val = arr[0], max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    // Step 2: Number of buckets
    int bucket_count = (max_val - min_val) / bucket_size + 1;

    // Create buckets
    int **buckets = (int **)malloc(bucket_count * sizeof(int *));
    int *bucket_counts = (int *)malloc(bucket_count * sizeof(int));
    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int)); // allocate max size for simplicity
        bucket_counts[i] = 0;
    }

    // Step 3: Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] - min_val) / bucket_size;
        buckets[idx][bucket_counts[idx]++] = arr[i];
    }

    // Step 4: Sort each bucket
    for (int i = 0; i < bucket_count; i++) {
        if (bucket_counts[i] > 0) {
            insert_sort(buckets[i], bucket_counts[i]);
        }
    }

    // Step 5: Concatenate buckets
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_counts[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucket_counts);
}

int parti(int arr[], int low, int high, int bit) {
    int i = low, j = high;
    while (i <= j) {
        while (i <= high && ((arr[i] >> bit) & 1) == 0) {
            i++;
        }
        while (j >= low && ((arr[j] >> bit) & 1) == 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    return i;
}

// Radix Exchange Sort
void radix_exchange_sort(int arr[], int low, int high, int bit) {
    if (low >= high || bit < 0) return;

    int mid = parti(arr, low, high, bit);

    // Recursively sort left and right partitions
    radix_exchange_sort(arr, low, mid - 1, bit - 1);
    radix_exchange_sort(arr, mid, high, bit - 1);
}

void insert_sorted(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// Address Calculation Sort
void address_calculation_sort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    // Create buckets
    Node** buckets = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // Map each element into bucket using address function
    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min) * n / (max - min + 1);
        insert_sorted(&buckets[index], arr[i]);
    }

    // Collect elements back into arr
    int k = 0;
    for (int i = 0; i < n; i++) {
        Node* current = buckets[i];
        while (current != NULL) {
            arr[k++] = current->data;
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}

int main(){
    int arr[] = {1, 3, 5, 4, 2};
    int n = 5;
    int choice;
    int bucket_size = 10;
    int max_val = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max_val) max_val = arr[i];

    int max_bits = 0;
    while (max_val > 0) {
        max_bits++;
        max_val >>= 1;
    }

    do {
        printf("\n--- Sort Algorithm Menu ---\n");
        printf(" 1. Insertion Sort\n 2. Bubble Sort\n 3. Selection Sort\n 4. Shell Sort\n 5. Quick Sort\n 6. Merge Sort\n 7. Heap Sort\n 8. Radix Sort\n 9. Counting Sort\n 10. Bucket Sort\n 11. Radix Exchange Sort\n 12. Address Calculation Sort\n 13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bubble_sort(arr, n);
                break;
            case 2:
                selection_sort(arr, n);
                break;
            case 3:
                insertion_sort(arr, n);
                break;
            case 4:
                shell_sort(arr, n);
                break;
            case 5:
                quick_sort(arr, 0, n-1);
                break;
            case 6:
                merge_sort(arr, 0, n-1);
                break;
            case 7:
                heap_sort(arr, n);
                break;
            case 8:
                radix_sort(arr, n);
                break;
            case 9:
                counting_sort(arr, n);
                break;
            case 10:
                bucket_sort(arr, n, bucket_size);
                break;
            case 11:
                radix_exchange_sort(arr, 0, n - 1, max_bits - 1);
                break;
            case 12:
                address_calculation_sort(arr, n);
                break;
            case 13:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 13);
    
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}