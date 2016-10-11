/*
usage: i.e. Sort a large set of floating point numbers which are in range from 0.0 to 1.0 
            and are uniformly distributed across the range
*/
void bucketSort(float* arr, int n) {
    // 1) Create n empty buckets - O(n)
    vector<float> b[n];
 
    // 2) Put array elements in different buckets - O(n)
    for (int i = 0; i < n; i++) { 
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets - O(n)
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());
 
    // 4) Concatenate all buckets into arr[] - O(n)
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}