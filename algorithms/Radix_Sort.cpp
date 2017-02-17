/*
    Time Compleixty: Long story, bro! See http://www.geeksforgeeks.org/radix-sort/
*/
 
void countSort(int* arr, int n, int exp) {
    int output[n]; // output array
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i] / exp) % 10 ]++;
 
    // Change count[i] so that count[i] now contains actual position of
    // this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    int indx;
    for (i = n - 1; i >= 0; i--) {
        indx = (arr[i] / exp) % 10;
        output[count[indx] - 1] = arr[i];
        count[indx]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to curent digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using Radix Sort
void radixsort(int* arr, int n) {
    // Find the maximum number to know number of digits
    int m = *max_element(arr, arr + n);
 
    // Do counting sort for every digit. Note that instead of passing digit
    // number, exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}