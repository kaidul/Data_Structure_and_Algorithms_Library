// game with n stones
// In a single move, a player can remove either 2, 3 or 5 stones
// Both players play optimally, player X will always play first
// 2, 3 or 5 can be choosen multiple times
void solve(int n) { // n stones
	vector<int> dp(n + 1, 0);
	dp[0] = 0; // 0 means loosing position
	dp[1] = 0;
	dp[2] = 1; // 1 means winning position
	dp[3] = 1;
	dp[4] = 1;
	dp[5] = 1;
	for(int i = 6; i <= n; i++) {
		dp[i] = !dp[i - 2] or !dp[i - 3] or !dp[i - 5];
	}
	return dp[n];
}

/***
Two players are playing a game on a 15 x 15 chessboard. The rules of the game are as follows:

The game starts with a single coin located at some coordinate. The coordinate of the upper left cell is [0, 0]
and the coordinate of the lower right cell is [14, 14].
In each move, a player must move the coin from cell (x, y) to one of the following locations:

x - 1, y - 2
x + 1, y - 2
x - 2, y + 1
x - 2, y - 1

Note: The coin must remain inside the confines of the board.

The players move in alternating turns. The first player who is unable to make a move loses the game.
***/

vector<bool> dp;
vector<bool> visited;

bool solve(int x, int y) {
	if(x < 0 or y < 0 or x >= n and y >= n) {
		return true;
	}
	if(visited[x][y]) {
		return dp[x][y];
	}
	bool ret = false;
	ret &= !solve(x - 1, y - 2);
	ret &= !solve(x + 1, y - 2);
	ret &= !solve(x - 2, y + 1);
	ret &= !solve(x - 2, y - 1);

	visited[x][y] = true;
	return dp[x][y] = ret;
}


// Given 'maxChoosableInteger', a player can choose any numbers from [1, 2 ...... maxChoosableInteger]
// The first player who can cause the running total exceed or equal 'desiredTotal' will win
// Each number can be used only once
// Both players play optimally

// utility function
bool canIWin(int maxChoosableInteger, int desiredTotal, int mask, vector<bool>& visited, vector<bool>& dp) {
    if(desiredTotal <= 0) {
        return false;
    }
    if(visited[mask]) {
        return dp[mask];
    }
    bool canWin = false;
    for(int i = 1; i <= maxChoosableInteger; i++) {
        if(!(mask & (1 << i))) {
            canWin |= !canIWin(maxChoosableInteger, desiredTotal - i, mask | (1 << i), visited, dp);
            if(canWin) {
                break;
            }
        }
    }
    visited[mask] = true;
    return dp[mask] = canWin;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if(maxChoosableInteger >= desiredTotal) {
        return true;
    }
    int totalPossible = (maxChoosableInteger * (maxChoosableInteger + 1)) / 2;
    if(totalPossible < desiredTotal) {
        return false;
    }
    int mask = 0;
    const int maxMask = 1 << (maxChoosableInteger + 1);
    vector<bool> dp(maxMask, false);
    vector<bool> visited(maxMask, false);
    return canIWin(maxChoosableInteger, desiredTotal, mask, visited, dp);
}