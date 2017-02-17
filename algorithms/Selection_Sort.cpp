/* Time: O(n^2) */
void selectionSort(int* arr, int n) {
    int minIndx;
    for(int i = 0; i < n - 1; i++) {
        minIndx = i;
        for(int j = i + 1; j < n; ++j) {
            if(arr[j] < arr[minIndx])
                minIndx = j;
        }
        swap(arr[i], arr[minIndx]);
    }
}