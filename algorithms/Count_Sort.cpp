/*
 Time: O(n + k); k = range of input
 Auxiliary space: O(n + k)
 */
void countSort(string& str) {
    // The output character array that will have sorted str
    char output[(int)str.length()];
    
    // Create a count array to store count of inidividul characters and
    // initialize count array as 0
    int count[RANGE + 1] = {0};
    
    // Store count of each character
    for(int i = 0; i < (int)str.length(); ++i)
        ++count[str[i]];
    
    // Change count[i] so that count[i] now contains actual position of
    // this character in output array
    for (int i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    
    // Build the output character array
    for (int i = 0; i < (int)str.length(); ++i) {
        output[count[str[i]] - 1] = str[i];
        --count[str[i]];
    }
    
    // Copy the output array to str, so that str now
    // contains sorted characters
    for(int i = 0; i < (int)str.length(); ++i)
        str[i] = output[i];
}