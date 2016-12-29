int lowerBound(vector<int>& arr, int target) {
    int n = (int)arr.size();
    int left = 0, right = n - 1;
    int indx = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            indx = mid;
        }
        if(arr[mid] < target) {
            left = mid + 1;
        } else { // arr[mid] >= target
            right = mid - 1;
        }
    }
    return indx;
}

// different from C++ upper_bound. return target's index inclusive
int upperBound(vector<int>& arr, int target) {
    int n = (int)arr.size();
    int left = 0, right = n - 1;
    int indx = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            indx = mid;
        }
        if(arr[mid] <= target) {
            left = mid + 1;
        } else { // arr[mid] > target
            right = mid - 1;
        }
    }
    return indx;
}

pair<int, int> equalRange(vector<int>& arr, int target) {
    int lbound = lowerBound(arr, target);
    int ubound = upperBound(arr, target);
    return pair<int, int>{lbound, ubound};
}

int binarySearch(vector<int>& arr, int target) {
    int lbound = lowerBound(arr, target);
    return lbound;
}