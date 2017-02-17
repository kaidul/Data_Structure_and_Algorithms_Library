/***
Alice and Bob are playing a game with a rooted tree. The tree has N vertices and the first node is 1, is always the root.
Here are the basic rules:
They move in alternating turns, and both players always move optimally.
During each move, a player removes an edge from the tree, disconnecting one of its leaves or branches.
The leaf or branch that was disconnected from the rooted tree is removed from the game.
The first player to be unable to make a move loses the game.
Alice always makes the first move.
***/

/***
Explanation:
This is a Green Hackenbush problem. We consider it to be green because each edge can be removed by either player. Because we're working with a tree, we can also easily apply the colon principle.

The colon principle states that, if a node is connected with n stalks of length l1, l2, l3....... ln - 1, then all of these stalks can be replaced with a single stalk of length l = l1 xor l2 xor l3 .... xor ln - 1. 

When using the colon principle on a tree, we can recursively convert the tree into a stalk. A stalk of length l is same as a single Nim pile of height l. This means that if we end up with a single Nim pile of positive height, Alice wins; otherwise, Bob wins.
***/

#define NODE 502
vector<int> adj[NODE + 10];

int hackenbush(int u, int parent) {
    
    int result = 0;
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        
        if (v == parent) continue;
        
        result ^= hackenbush (v, u) + 1;
    };
    
    return result;
}
// int res = hackenbush (1, 0);
// if ( res ) printf ( "Alice\n" );
// else printf ( "Bob\n" );