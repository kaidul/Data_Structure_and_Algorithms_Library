/*
 Time Complexity: O(n^2)
 Goal is to sort the sequence in as few reversals as possible
 */

/* Reverses arr[0..k] */
void flip(vector<int>& arr, int k) {
    for(int left = 0, right = k; left < right; ++left, --right) {
        swap(arr[left], arr[right]);
    }
}

/* Returns index of the maximum element in arr[0..n-1] */
int findMax(vector<int>& arr, int k) {
    int Max = 0;
    for (int i = 0; i < k; ++i) {
        if(arr[i] > arr[Max]) {
            Max = i;
        }
    }
    return Max;
}

void pancakeSort(vector<int>& arr) {
    // Start from the complete array and one by one reduce current size by one
    for (int n = (int)arr.size(), k = n; k > 1; --k) {
        // Find index of the maximum element in arr[0..k - 1]
        int mIndx = findMax(arr, k);
        
        // Move the maximum element to end of current array if it's not
        // already at the end
        if (mIndx != k - 1) {
            // To move at the end, first move maximum number to beginning
            flip(arr, mIndx);
            
            // Now move the maximum number to end by reversing current array
            flip(arr, k - 1);
        }
    }
}