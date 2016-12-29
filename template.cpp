//  Created by Kaidul Islam on 18/4/16.
//  Copyright © 2016 Kaidul Islam. All rights reserved.
//
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// #include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for(__typeof(n) i = 0; i < (n); i++)
#define rrep(i, n) for(__typeof(n) i = (n) - 1; i >= 0; --i)
#define rep1(i, n) for(__typeof(n) i = 1; i <= (n); i++)
#define FOR(i, a, b) for(__typeof(b) i = (a); i <= (b); i++)
#define forstl(i, s) for (__typeof ((s).end ()) i = (s).begin (); i != (s).end (); ++i)
#define SIZE(v) ((int)v.size())
#define INF (1 << 30)
#define PI acos(-1.0)
#define bitcnt __builtin_popcount
#define pb push_back
#define ppb pop_back
#define all(x) x.begin(), x.end()
#define mem(x, y) memset(x, y, sizeof x)
#define eps 1e-9
#define pii pair<int, int>
#define couple make_pair
#define X first
#define Y second
#define vi vector<int>
#define vpii vector< pii >
#define si set<int>
#define SDi(x) sf("%d", &x)
#define SD2(x, y) sf("%d %d", &x, &y)
#define SD3(x, y, z) sf("%d %d %d", &x, &y, &z)
#define SDs(x) sf("%s", x)
#define pf printf
#define print(x) pf("%d ", x)
#define println(x) pf("%d\n", x)
#define output(x, y); pf("Case %d: %d", ++x, y)
#define newLine pf("\n")
#define sf scanf
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
#if ( _WIN32 or __WIN32__ )
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define SDl(x) sf(LLD, &x)
#define MAX5 100000
#define MAX7 10000000
#define MAX9 1000000000
#define MOD7 (MAX7 + 7)
#define MOD9 (MAX9 + 9)
typedef long long i64;
typedef unsigned long long ui64;
const i64 INF64 = (i64) 1E18;

template<typename T> string toStr(T n) { ostringstream oss; oss << n; oss.flush(); return oss.str(); }
template<typename T> T toInt(string s) { T n = 0; istringstream sin(s); sin >> n; return n; }

class TimeTracker {
    clock_t start, end;
public:
    TimeTracker() {
        start = clock();
    }
    ~TimeTracker() {
        end = clock();
        fprintf(stderr, "%.3lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
};

struct Point {
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b): x(a), y(b) {}
    bool operator < (const Point& other) const {
        return x < other.x;
    }
};
// BitMask
int Set(int N, int pos) {
    return N |= (1 << pos);
}
int Reset(int N, int pos) {
    return N &= ~(1 << pos);
}
int Check(int N, int pos) {
    return (N & (1 << pos));
}
int toggle(int N, int pos) {
    return N ^= (1 << pos);
}

// direction array
//int dx[] = {0, -1, 0, 1};
//int dy[] = {-1, 0, 1, 0};
//int Dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
//int Dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
//int _row, _col;
//inline bool isValid(int i, int j) {
//    return i >= 0 and j >= 0 and i < _row and j < _col;
//}

#define MOD (MAX9 + 7)

inline void IncMod(int &x, int y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

#define keyType int
class Compare {
public:
    bool operator() (keyType& lhs, keyType& rhs) const {
        return lhs > rhs;
    }
} compare;
// e.g. sort(all(arr), compare)


#define error(args...) { vector<string> _v; split(#args, ',', _v); err(_v.begin(), args); }

void split(const string& s, char c, vector<string>& result) {
    stringstream ss(s);
    string x;
    while (getline(ss, x, c))
        result.push_back(x);
}

void err(vector<string>::iterator it) {}
template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
    cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
    err(++it, args...);
}

/*
 error(a, b, c)
output:
 a = 4
 b = 8
 c = 9
*/

/** Implementation **/

int main(int argc, const char * argv[]) {
#ifndef ONLINE_JUDGE
    READ("input.txt");
#endif
    int tcase;
    SDi(tcase);
    while(tcase--) {
        
    }
    return 0;
}