/***
Z[i] is the length of the longest common prefix between s and the suffix of s starting at i.
Example:
s = 'aaabaab'

z[0] = 0,
z[1] = 2,
z[2] = 1,
z[3] = 0,
z[4] = 2,
z[5] = 1,
z[6] = 0.
s = 'abacaba'

z[0] = 0,
z[1] = 0,
z[2] = 1,
z[3] = 0,
z[4] = 3,
z[5] = 0,
z[6] = 1.

Applications:
1. searching substring: find all occurances of pattern in O(n) + O(m) time
2. find all unique substrings of strings
3. string compression: find a string t of shortest length such that s can be represented as a concatenation of one or more copies of t.

See: https://www.hackerrank.com/challenges/string-similarity/topics/z-function
***/

vector<int> Z;

// O(n)
void zFunction(string const& s) {
    int n = (int) s.length();
    Z = vector<int>(n);
    for(int i = 1, left = 0, right = 0; i < n; ++i) {
        if (i <= right) {
            Z[i] = min (right - i + 1, Z[i - left]);
        }
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            ++Z[i];
        }
        if (i + Z[i] - 1 > right) {
            left = i;
            right = i + Z[i] - 1;
        }
    }
}