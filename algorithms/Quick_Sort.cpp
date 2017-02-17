/*
Time: O(nlogn)
Extra Space: O(logn)
This function takes last element as pivot, places the pivot element at its
correct position in sorted array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right of pivot
*/
int partition (int* arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;  // Index of smaller element
 
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);  // Swap current element with index
    }
    swap(arr[++i], arr[right]);
    return i;
}
 
void quickSort(int* arr, int left, int right) {
    if (left < right) {
        int pos = partition(arr, left, right);
        quickSort(arr, left, pos - 1);
        quickSort(arr, pos + 1, right);
    }
}