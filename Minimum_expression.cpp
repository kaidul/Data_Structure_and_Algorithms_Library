// return the position of rotation of a string such that 
// the resulting string is lexicographically smallest
// Time : O(n)
// https://www.quora.com/How-does-the-minimum-expression-algorithm-by-Zhou-Yuan-work
int minimumExpression(string s) {
	s += s;
    size_t n = s.length();
    int i = 0, j = 1, k = 0;
    while(i + k < n and j + k < n) {
        if(s[i + k] == s[j + k]) k++;
        else if(s[i + k] > s[j + k]) {
        	i = i + k + 1; 
        	if(i <= j) i = j + 1; 
        	k = 0;
        }
        else if(s[i + k] < s[j + k]) {
        	j = j + k + 1;
        	if(j <= i) j = i + 1;
        	k = 0;
        }
    }
    return min(i, j);	
}