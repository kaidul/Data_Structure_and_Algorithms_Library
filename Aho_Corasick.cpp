// Aho-Corasick Algorithm
// like unix fgrep - applicable when there are multiple patterns
// O(m + n + z) where m is total length of patterns, n is text length and z is number of occurance
// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const int MAX_STATE = 500;

const int MAX_CHAR = 26; // 256

// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
int output[MAX_STATE];

int failure[MAX_STATE];

int trie[MAX_STATE][MAX_CHAR];

// Builds the string matching machine.
// arr -   array of words. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i]
//         in the text.
// Returns the number of states that the built machine has.
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(vector<string>& pattern)
{
    int n = (int)pattern.size();
    // Initialize all values in output function as 0.
    memset(output, 0, sizeof output);
    
    // Initialize all values in goto function as -1.
    memset(trie, -1, sizeof trie);
    
    // Initially, we just have the 0 state
    int states = 1;
    
    // ##### Build Trie #######
    
    for (int i = 0; i < n; ++i) {
        const string& word = pattern[i];
        int currentState = 0;
        
        for (int j = 0; j < word.size(); ++j) {
            int ch = word[j] - 'a';
            if (trie[currentState][ch] == -1) {
                trie[currentState][ch] = states++;
            }
            currentState = trie[currentState][ch];
        }
        
        output[currentState] |= (1 << i);
    }
    
    // For all characters which don't have an edge from
    // root (or state 0) in Trie, add a goto edge to state
    // 0 itself
    for (int ch = 0; ch < MAX_CHAR; ++ch) {
        if(trie[0][ch] == -1) {
            trie[0][ch] = 0;
        }
    }
    
    // ##### Build Failure function #######
    
    // Initialize values in fail function
    memset(failure, -1, sizeof failure);
    
    // Failure function is computed in breadth first order
    // using a queue
    queue<int> q;
    
    // Iterate over every possible input
    for (int ch = 0; ch < MAX_CHAR; ++ch) {
        // All nodes of depth 1 have failure function value
        if (trie[0][ch] != 0) {
            failure[trie[0][ch]] = 0;
            q.push(trie[0][ch]);
        }
    }
    
    // Noe queue contains all nodes of depth 1
    while (q.size()) {
        int state = q.front();
        q.pop();
        
        // For the removed state, find failure function for
        // all those characters for which goto function is defined.
        for (int ch = 0; ch <= MAX_CHAR; ++ch) {
            // If goto function is defined for character 'ch' and 'state'
            if (trie[state][ch] != -1) {
                // Find failure state of removed state
                int f = failure[state];
                
                // Find the deepest node labeled by proper
                // suffix of string from root to current
                // state.
                while (trie[f][ch] == -1) {
                    f = failure[f];
                }
                
                f = trie[f][ch];
                failure[trie[state][ch]] = f;
                
                // Merge output values
                output[trie[state][ch]] |= output[f];
                
                // Insert the next level node (of Trie) in Queue
                q.push(trie[state][ch]);
            }
        }
    }
    
    return states;
}

// Returns the next state the machine will transition to using goto and failure functions.
// currentState - The current state of the machine. Must be between 0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine.
int findNextState(int currentState, char nextInput) {
    int answer = currentState;
    int ch = nextInput - 'a';
    
    // If goto is not defined, use failure function
    while (trie[answer][ch] == -1) {
        answer = failure[answer];
    }
    
    return trie[answer][ch];
}

// This function finds all occurrences of all array words
// in text.
void searchWords(vector<string>& pattern, string text) {
    int n = (int)pattern.size();
    // Preprocess patterns.
    // Build machine with goto, failure and output functions
    buildMatchingMachine(pattern);
    
    // Initialize current state
    int currentState = 0;
    
    // Traverse the text through the nuilt machine to find
    // all occurrences of words in arr[]
    for (int i = 0; i < text.size(); ++i) {
        currentState = findNextState(currentState, text[i]);
        
        // If match not found, move to next state
        if (output[currentState] == 0) continue;
        
        // Match found, print all matching words of arr[]
        // using output function.
        for (int j = 0; j < n; ++j) {
            if (output[currentState] & (1 << j)) {
                cout << "Word " << pattern[j] << " appears from " << i - pattern[j].size() + 1 << " to " << i << endl;
            }
        }
    }
}

/*
vector<string> pattern{"he", "she", "his", "hers"};
string text = "ahishers";
searchWords(pattern, text);
*/