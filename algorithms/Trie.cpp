const static int SIZE = 30;
const static int NOT_FOUND = -1;
class trie {
private:
    struct trieNode {
        int mark;
        trieNode* children[SIZE];
        trieNode(): mark(NOT_FOUND) {
            for (int i = 0; i < SIZE; ++i) {
                children[i] = nullptr;
            }
        }
        ~trieNode() {
            for (int i = 0; i < SIZE; ++i) {
                delete children[i];
                children[i] = nullptr;
            }
        }
    };
    trieNode* root;
public:
    trie(): root(new trieNode()) {
    }
    ~trie() {
        delete root;
        root = nullptr;
    }
    
    void insert(string const& key, int id) {
        trieNode* pCrawl = root;
        for (int i = 0; i < (int)key.length(); ++i) {
            int indx = key[i] - 'a';
            if (!pCrawl->children[indx]) {
                pCrawl->children[indx] = new trieNode();
            }
            pCrawl = pCrawl->children[indx];
        }
        pCrawl->mark = id;
    }
    
    int search(string const& key) {
        trieNode *pCrawl = root;
        for (int i = 0; i < (int)key.length(); ++i) {
            int indx = key[i] - 'a';
            if (!pCrawl->children[indx]) {
                return NOT_FOUND;
            }
            pCrawl = pCrawl->children[indx];
        }
        return pCrawl->mark;
    }
};    
