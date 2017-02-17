// O(n^2)
for(int i = 0; i < n; ++i)
    for(int j = 0, m = n - i - 1; j < m; ++j)
        if(arr[j] > arr[j + 1])
            swap(arr[j], arr[j + 1]);