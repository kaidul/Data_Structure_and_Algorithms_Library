// A Huffman tree node
struct MinHeapNode {
    char data;                 // One of the input characters
    unsigned freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
    MinHeapNode(char data, unsigned freq): data(data), freq(freq), left(nullptr), right(nullptr) {
    }
};

struct compare {
    bool operator()(MinHeapNode* lhs, MinHeapNode* rhs) {
        return (lhs->freq > rhs->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str) {
    if (!root) return;
    if (root->data != '$') {
        cout << root->data << ": " << str << "\n";
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void huffmanCodes(unordered_map<char, int>& freqMap) {
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for(auto iter = freqMap.begin(); iter != freqMap.end(); ++iter) {
        minHeap.push(new MinHeapNode(iter->first, iter->second));
    }
    while (minHeap.size() != 1) {
        MinHeapNode* left = minHeap.top();
        minHeap.pop();
        MinHeapNode* right = minHeap.top();
        minHeap.pop();
        MinHeapNode* newNode = new MinHeapNode('#', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    
    printCodes(minHeap.top(), "");
}