struct node {
    int data;
    struct node *next;
};
 
/* Given a reference (pointer to pointer) to the head of a list and an int,
   inserts a new node on the front of the list.
  Time: O(1)
   */
void push(struct node** head_ref, int new_data) {
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
 
    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}
 
/* Given a node prev_node, insert a new node after the given prev_node
   Time: O(1)
*/
void insertAfter(struct node* prev_node, int new_data) {
    /*1. check if the given prev_node is NULL */
    assert(prev_node != NULL);
 
    /* 2. allocate new node */
    struct node* new_node =(struct node*) malloc(sizeof(struct node));
 
    /* 3. put in the data  */
    new_node->data = new_data;
 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
 
    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}
 
/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end
   Time: O(n)
*/
void append(struct node** head_ref, int new_data) {
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. This new node is going to be the last node, so make next of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
 
    struct node *last = *head_ref;  /* used in step 5*/
 
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
 
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}
 
/* Given a reference (pointer to pointer) to the head of a list
   and a key, deletes the first occurrence of key in linked list
   Time: O(n)
*/
void deleteNode(struct node **head_ref, int key) {
    // Store head node
    struct node* temp = *head_ref, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL and temp->data == key) {
        *head_ref = temp->next;   // Changed head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL and temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL) return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
}
 
void traverse(struct node *n) {
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
}
 
/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
                    struct node** frontRef, struct node** backRef);
 
/* sorts the linked list by changing next pointers (not data)
   Time: O(nlogn)
*/
void MergeSort(struct node** headRef) {
    struct node* head = *headRef;
    struct node* a, *b;
 
    /* Base case -- length 0 or 1 */
    if (head == NULL or head->next == NULL)
        return;
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this
   function */
struct node* SortedMerge(struct node* a, struct node* b) {
    struct node* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);
 
    /* Pick either a or b, and recur */
    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}
 
/*
 * @param head: head node
 * @param move: the node needed to be inserted
 * return: the node before the insertion position
 */
ListNode *find_insertion_position(ListNode *head, ListNode *move) {
    while(head->next && head->next->val <= move->val) {
        head = head->next;
    }
    return head;
}
 
// insertion sort
ListNode *insertionSortList(ListNode *head) {
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *iter = head;
    ListNode *sentinel = new ListNode(numeric_limits<int>::min());
    while(iter) {
        ListNode *next = iter->next;
 
        ListNode *insert_pos = find_insertion_position(sentinel, iter);
        iter->next = insert_pos->next;
        insert_pos->next = iter;
        iter = next;
    }
    return sentinel->next;
}
 
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct node* source,
                    struct node** frontRef, struct node** backRef) {
    struct node* fast;
    struct node* slow;
    if (source == NULL or source->next == NULL) {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;
 
        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
 
        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}