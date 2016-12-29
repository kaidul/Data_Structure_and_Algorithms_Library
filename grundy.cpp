// Grundy problem's solution basic pattern
def grundyNumber (current_state):
    moves[] = possible positions to which I can move from current_state
    set X;
    for (all new_state in moves) 
		X.insert(grundyNumber(new_state));
      
    int ret = 0;
    while (s.contains(ret)) 
    	ret++;
    # ret is the smallest non-negative integer not in the set s; 
    
    return ret;
end

// Example #1
/**
There are two players, First and Second, sitting in front of a pile of n stones. First always plays first.
There is a set S, of m distinct integers defined as {s1, s2, s3 ... sm}.
The players move in alternating turns. During each turn, a player chooses some si
and splits one of the piles into exactly si smaller piles of equal size. 
If no si exists that will split one of the available piles into exactly si equal smaller piles, the player loses.
Both players always play optimally.
**/
/** Implementation **/

#define MAX 10
i64 divisors[MAX + 1];
i64 n;
int m;
unordered_map<i64, i64> dp;

i64 grundy(i64 x) {
    if(x == 1LL) return 0LL;
    if(dp.count(x)) return dp[x];
    unordered_set<i64> visited;
    rep(i, m) {
        i64 y = divisors[i];
        if(y > x) { break; }
        if(x % y != 0LL) {
            continue;
        }
        i64 z = x / y;

        i64 g = grundy(z);
        if(y & 1LL) { g = g; }
        else { g = 0LL; }

        visited.insert(g);
    }
    i64 ret = 0LL;
    while(visited.count(ret)) { ++ret; }

    return dp[x] = ret;
}

int main() {
    SDl(n); SDi(m);
    rep(i, m) {
        SDl(divisors[i]);
    }
    sort(divisors, divisors + m);
    if(grundy(n)) {
        puts("First");
    } else {
        puts("Second");
    }
    return 0;
}

// #Example #2
// Zero nim game: rules are of exactly nim game
// exept zero stone can be picked from any piles exactly once 

// Similar example: game with nim rules but any player can pick one or two stones only
/** Implementation **/

#define MAX 2005
int piles[MAX];
unordered_map<int, unordered_map<bool, int>> dp;
int n;

int grundyRecur(int x, bool zeroPicked = false) {
    if(x == 0) return 0;
    if(dp[x][zeroPicked]) return dp[x][zeroPicked];
    unordered_set<int> visited;
    FOR(i, 0, x) {
        if(i == 0 and zeroPicked) {
            continue;
        }
        int g = grundyRecur(x - i, i == 0 or zeroPicked);
        visited.insert(g);
    }
    int ret = 0;
    while(visited.count(ret)) { ++ret; }
    
    return dp[x][zeroPicked] = ret;
}

int calcGrundy() {
    int Xor = 0;
    for(int i = 0; i < n; i++) {
        Xor ^= grundyRecur(piles[i]);
    }
    return Xor;
}

// After observation, its turns out grundy[odd] = odd + 1 and grundy[even] = even - 1 except 0
int calcGrundy2() {
    int Xor = 0;
    for(int i = 0; i < n; i++) {
        if(piles[i] == 0) {
            continue;
        }
        int g = ((piles[i] & 1) ? piles[i] + 1 : piles[i] - 1);
        Xor ^= g;
    }
    return Xor;
}

int main() {
    int tcase;
    cin >> tcase;
    while(tcase--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> piles[i];
        }
        int grundy = calcGrundy2();
        if(grundy > 0) {
            puts("First");
        } else {
            puts("Second");
        }
    }
    return 0;
}

// # Example #3
/***
Two players are playing a game on a 15 x 15 chessboard. The rules of the game are as follows:

The game starts with a k coins located at some coordinate(one cell can contain more than one coin).
The coordinate of the upper left cell is [1, 1] and the coordinate of the lower right cell is [15, 15].
In each move, a player must move any coin from cell (x, y) to one of the following locations:

x - 1, y - 2
x + 1, y - 2
x - 2, y + 1
x - 2, y - 1

Note: The coin must remain inside the confines of the board.

The players move in alternating turns. The first player who is unable to make a move loses the game.
***/
#define MAX 15
bool visited[MAX * 2 + 1];
int grundy[MAX * 2 + 1][MAX * 2 + 1];
int dx[4] = {-1, +1, -2, -2};
int dy[4] = {-2, -2, +1, -1};

inline bool isValid(int x, int y) {
    return (x > 0 and y > 0 and x <= MAX and y <= MAX);
}

// without preprocess
int dp[MAX][MAX];
int calcGrundy(int x, int y) {
	if(!isValid(x, y)) {
		return -1;
	}
	if(dp[x][y] != -1) {
		return dp[x][y];
	}
	unordered_set<int> visited;
	visited.insert(calcGrundy(x - 1, y - 2));
	visited.insert(calcGrundy(x + 1, y - 2));
	visited.insert(calcGrundy(x - 2, y + 1));
	visited.insert(calcGrundy(x - 2, y - 1));

	int ret = 0;
    while(visited.count(ret)) {
    	++ret;
    }
    return dp[x][y] = ret;
}

void preprocess() {
    for(int k = 2; k <= MAX * 2; ++k) { // for safety, MAX * 2 is not the exact dimension
        for(int x = 1; x < k; ++x) {
            int y = k - x;
            if(!isValid(x, y)) {
                continue;
            }
            memset(visited, false, sizeof visited);
            for(int i = 0; i < 4; ++i) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                if(isValid(newX, newY)) {
                    visited[grundy[newX][newY]] = true;
                }
            }
            int g;
            for(g = 0; visited[g]; ++g);
            grundy[x][y] = g;
        }
    }
}

int main() {
    int tcase;
    int k;
    int x, y;
    preprocess();
    scanf("%d", &tcase);
    while(tcase--) {
        scanf("%d", &k);
        int Xor = 0;
        for(int i = 0; i < k; ++i) {
            scanf("%d %d", &x, &y);
            Xor ^= grundy[x][y];
        }
        if(Xor) {
            puts("First");
        } else {
            puts("Second");
        }
    }
    return 0;
}