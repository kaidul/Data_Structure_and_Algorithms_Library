// first player wins if XOR > 0
// second player wins otherwise
// return true if first player wins
bool nim(vector<int>& piles) {
	int Xor = 0;
	int n = piles.size();
	for(int i = 0; i < n; i++) {
		Xor ^= piles[i];
	}
	return (Xor > 0);
}

// Nim variant #1
// Misère Nim
// Classical nim except the player who removes the last stone will loose
bool misereNim(vector<int>& piles) {
	int Xor = 0;
	int n = (int)piles.size();
	bool allOnes = true;
	for(int i = 0; i < n; i++) {
		if(piles[i] != -1) {
			allOnes = false;
			break;
		}
		Xor ^= piles[i];
	}
	if(allOnes) {
		return false;
	}
	return (Xor > 0);
}

// Nim variant #2
// Nimble game
/***
Two people are playing Nimble! The rules of the game are:

The game is played on a line of n squares, indexed from 0 to n - 1. Each square i (where i < n) contains ci coins
nimble.png
The players move in alternating turns. During each move, the current player must remove exactly 1 coin from square i and move it to square j
if and only if j < i.
The game ends when all coins are in square 0 and nobody can make a move. The first player to have no available move loses the game.
***/
bool nimble(vector<int>& squares) {
	int n = (int)squares.size();
	int Xor = 0;
	for(int i = 0; i < n; i++) {
		// optimization: xoring i with Xor 'squares[i]' times
		if(squares[i] & 1) {
			Xor ^= i;
		}
	}
	return (Xor > 0);
}

// Nim variant #3
// Poker nim
// Bogus nim: Exactly nim except now 
// any player can add one or more stones to any piles
bool pokerNim(vector<int>& piles) {
	// adding stones has no effect as in the next turn, the other player can mimic the first player turn
	// and remove same number of stones
	return nim(piles);
}

// NIm variant #4
// Prime power game
// Given a number, any player can divide the number of with power of prime
// whoever has no turn left and found the number 1, will loose
// n = 56700 = 2^2 × 3^4 × 5^2 × 7^1 turn out as nim game with {2, 4, 2, 1} piles
// similiar problem: https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-2
bool primePower(int n) {
	vector<int>factors;
	primeFactors(n, factors);
	return nim(factors);
}