#ifndef BST_H
#define BST_H
template <typename T>
class treeNode {
public:
    treeNode *left;
    treeNode *right;
    T key;
    treeNode(T key)
        : key(key)
        , left(nullptr)
        , right(nullptr) {
    }
};
 
template <typename T>
class BST {
public:
    BST() {
        root = nullptr;
        nodes = 0;
    }
 
    BST(BST const& rhs)
        : nodes(rhs.size()) {
        // not yet implemented
    }
 
    BST& operator = (BST rhs) {
        this->swap(rhs);
    }
 
    BST& operator = (BST&& rhs) {
        this->swap(rhs);
    }
 
    ~BST() {
        clear(root);
    }
 
    void swap(BST& other) {
        std::swap(root, other.root);
        std::swap(nodes, other.nodes);
    }
 
    void clear(treeNode<T>* node) {
        if(node) {
            if(node->left) clear(node->left);
            if(node->right) clear(node->right);
            delete node;
        }
    }
 
    bool isEmpty() const {
        return root == nullptr;
    }
    void inorder(treeNode<T>*);
    void traverseInorder();
 
    void preorder(treeNode<T>*);
    void traversePreorder();
 
    void postorder(treeNode<T>*);
    void traversePostorder();
 
    void insert(T const& );
 
    void remove(T const& );
 
    treeNode<T>* search(const T &);
 
    treeNode<T>* minHelper(treeNode<T>*);
    treeNode<T>* min();
 
    treeNode<T>* maxHelper(treeNode<T>*);
    treeNode<T>* max();
 
    size_t size() const;
 
    void sort();
    treeNode<T>* inOrderSuccessor(treeNode<T>*);
    bool isBST(treeNode<T>*) const;
    bool isBST() const;
 
private:
    treeNode<T> *root;
    size_t nodes;
};
 
// Smaller elements go left
// larger elements go right
template <class T>
void BST<T>::insert(T const& value) {
    treeNode<T> *newNode = new treeNode<T>(value);
    treeNode<T> *parent = nullptr;
 
    // is this a new tree?
    if(isEmpty()) {
        root = newNode;
        ++nodes;
        return;
    }
    //Note: ALL insertions are as leaf nodes
    treeNode<T>* curr = root;
    // Find the Node's parent
    while(curr) {
        parent = curr;
        curr = newNode->key > curr->key ? curr->right : curr->left;
    }
 
    if(newNode->key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
 
    ++nodes;
}
 
template <typename T>
void BST<T>::remove(T const& data) {
 
    if(isEmpty()) {
        throw std::runtime_error("Invalid Action!");
    }
 
    treeNode<T> *curr = root;
    treeNode<T> *parent;
 
    // root to leaf search (top-down)
    while(curr) {
        if(curr->key == data) {
            break;
        } else {
            parent = curr;
            curr = data > curr->key ? curr->right : curr->left;
        }
    }
 
    if(curr == nullptr) {
        cout << "key not found! " << endl;
        return;
    }
 
 
    // 3 cases :
    // 1. We're removing a leaf node
    // 2. We're removing a node with a single child
    // 3. we're removing a node with 2 children
 
 
    //We're looking at a leaf node
    if( curr->left == nullptr and curr->right == nullptr) {
        if(parent->left == curr)
            parent->left = nullptr;
        else
            parent->right = nullptr;
 
        delete curr;
        --nodes;
        return;
    }
 
    // Node with single child
    if((curr->left == nullptr and curr->right != nullptr) or (curr->left != nullptr and curr->right == nullptr)) {
        if(curr->left == nullptr and curr->right != nullptr) {
            if(parent->left == curr) {
                parent->left = curr->right;
            } else {
                parent->right = curr->right;
            }
        } else { // left child present, no right child
            if(parent->left == curr) {
                parent->left = curr->left;
            } else {
                parent->right = curr->left;
            }
        }
        delete curr;
        --nodes;
        return;
    }
 
    // Node with 2 children
    // replace node with smallest value in right subtree
    if (curr->left != nullptr and curr->right != nullptr) {
        treeNode<T> *curr_right = curr->right;
        if(curr_right->left == nullptr and curr_right->right == nullptr) {
            curr->key = curr_right->key;
            delete curr_right;
            curr->right = nullptr;
        } else { // right child has children
            //if the node's right child has a left child
            // Move all the way down left to locate smallest element
 
            if((curr->right)->left != nullptr) {
                treeNode<T>* lcurr;
                treeNode<T>* lcurr_parent;
                lcurr_parent = curr->right;
                lcurr = (curr->right)->left;
                while(lcurr->left != nullptr) {
                    lcurr_parent = lcurr;
                    lcurr = lcurr->left;
                }
                curr->key = lcurr->key;
                delete lcurr;
                lcurr_parent->left = nullptr;
            } else { // (curr->right)->right != nullptr
                treeNode<T> *tmp = curr->right;
                curr->key = tmp->key;
                curr->right = tmp->right;
                delete tmp;
            }
        }
        --nodes;
    }
 
}
 
template <typename T>
treeNode<T>* BST<T> :: search(T const& value) {
    treeNode<T> *curr = root;
    while (curr) {
        if(curr->key == value) {
            return curr;
        } else if(value < curr->key) {
            curr = curr->left;
        } else curr = curr->right;
    }
    return nullptr;
}
 
template <typename T>
treeNode<T>* BST <T> :: minHelper(treeNode<T>* node) {
    if(node->left == nullptr)
        return node;
    minHelper(node->left);
}
 
template <typename T>
treeNode<T>* BST <T> :: min() {
    return minHelper(root);
}
 
template <typename T>
treeNode<T>* BST <T> :: maxHelper(treeNode<T>* node) {
    if(node->right == nullptr)
        return node;
    maxHelper(node->right);
}
 
template <typename T>
treeNode<T>* BST <T> :: max() {
    return maxHelper(root);
}
 
template<typename T>
size_t BST<T>::size() const {
    return nodes;
}
 
template<typename T>
void BST<T>::inorder(treeNode<T>* node) {
    if(node != nullptr) {
        if(node->left) inorder(node->left);
        cout << " " << node->key << " ";
        if(node->right)
            inorder(node->right);
    }
}
 
template<typename T>
void BST<T>::traverseInorder() {
    inorder(root);
}
 
template<typename T>
void BST<T>::sort() {
    inorder(root);
}
 
template<typename T>
void BST<T>::preorder(treeNode<T>* node) {
    if(node != nullptr) {
        cout << " " << node->key << " ";
        if(node->left) preorder(node->left);
        if(node->right) preorder(node->right);
    }
}
 
template<typename T>
void BST<T>::traversePreorder() {
    preorder(root);
}
 
template<typename T>
void BST<T>::postorder(treeNode<T>* node) {
    if(node != nullptr) {
        if(node->left) postorder(node->left);
        if(node->right) postorder(node->right);
        cout << " " << node->key << " ";
    }
}
 
template<typename T>
void BST<T>::traversePostorder() {
    postorder(root);
}
 
// source: http://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree
template <class T>
treeNode<T>* BST<T> :: inOrderSuccessor(treeNode<T>* node) {
    if(node->right != nullptr)
        return minHelper(node->right);
 
    treeNode<T>* succ = nullptr;
    treeNode<T>* curr = root;
    // Start from root and search for successor down the tree
    while (curr != nullptr) {
        if (node->key < curr->key) {
            succ = curr;
            curr = curr->left;
        } else if (node->key > curr->key)
            curr = curr->right;
        else
            break;
    }
    return succ;
}
 
template<typename T>
bool BST<T>::isBST(treeNode<T>* node) const {
    static struct treeNode<T> *prev = nullptr;
 
    // traverse the tree in inorder fashion and keep track of prev node
    if (node) {
        if (!isBST(node->left))
            return false;
 
        // Allows only distinct valued nodes
        if (prev != nullptr and node->key <= prev->key)
            return false;
 
        prev = node;
 
        return isBST(node->right);
    }
 
    return true;
}
 
template<typename T>
bool BST<T>::isBST() const {
    return isBST(root);
}
#endif // BST_H