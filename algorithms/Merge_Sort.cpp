/*
Time: O(nlogn)
Extra Space: Omega(n) [O(n) + O(logn) = allocating n elements + stack frame]
*/
void merge(int* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++) L[i] = arr[left + i];
    for(j = 0; j <= n2; j++) R[j] = arr[mid + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0, j = 0, k = left;
    while (i < n1 and j < n2)
        arr[k++] = L[i] <= R[j] ? L[i++] : R[j++];
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
        arr[k++] = L[i++];
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
        arr[k++] = R[j++];
}
 
void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; //Same as (l + r) / 2, but avoids overflow for large left and right
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}