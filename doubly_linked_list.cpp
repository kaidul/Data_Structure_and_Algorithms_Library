struct node {
    int data;
    struct node *next, *prev;
};
 
/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct node** head_ref, int new_data) {
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;
 
    /* 4. change prev of head node to new node */
    if((*head_ref) !=  NULL)
        (*head_ref)->prev = new_node ;
 
    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;
}
 
/* Given a node as prev_node, insert a new node after the given node */
void insertAfter(struct node* prev_node, int new_data) {
    /*1. check if the given prev_node is NULL */
    assert(prev_node != NULL);
 
    /* 2. allocate new node */
    struct node* new_node =(struct node*) malloc(sizeof(struct node));
 
    /* 3. put in the data  */
    new_node->data  = new_data;
 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
 
    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;
 
    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;
 
    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}
 
/* Given a node as next_node, insert a new node before the given node */
void insertBefore(struct node* next_node, int new_data) {
    assert(next_node != NULL);
    struct node* new_node =(struct node*) malloc(sizeof(struct node));
    new_node->data  = new_data;
    new_node->next = next_node;
    if(next_node->prev != NULL) {
        next_node->prev->next = new_node;
        new_node->prev = next_node->prev;
    }
    next_node->prev = new_node;
}
 
/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new node at the end  */
void append(struct node** head_ref, int new_data) {
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    struct node *last = *head_ref;  /* used in step 5*/
 
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
 
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
 
    /* 6. Change the next of last node */
    last->next = new_node;
 
    /* 7. Make last node as previous of new node */
    new_node->prev = last;
 
    return;
}
 
/* Function to delete a node in a Doubly Linked List.
   head_ref --> pointer to head node pointer.
   del  -->  pointer to node to be deleted. */
void deleteNode(struct node **head_ref, struct node *del) {
    /* base case */
    if(*head_ref == NULL or del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if(*head_ref == del)
        *head_ref = del->next;
 
    /* Change next only if node to be deleted is NOT the last node */
    if(del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be deleted is NOT the first node */
    if(del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}
 
/* Quick Sort
   Time: best & average O(nlogn), worst O(n^2)
 */
 
struct node *lastNode(node *head) {
    while (head and head->next)
        head = head->next;
    return head;
}
 
/* Considers last element as pivot, places the pivot element at its
   correct position in sorted array, and places all smaller (smaller than
   pivot) to left of pivot and all greater elements to right of pivot */
node* partition(node *left, node *right) {
    // set pivot as h element
    int x  = right->data;
 
    // similar to i = l-1 for array implementation
    node *i = left->prev;
 
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (node *j = left; j != right; j = j->next) {
        if (j->data <= x) {
            // Similar to i++ for array
            i = (i == NULL) ? left : i->next;
 
            swap(i->data, j->data);
        }
    }
    i = (i == NULL) ? left : i->next; // Similar to i++
    swap(i->data, right->data);
 
    return i;
}
 
/* A recursive implementation of quicksort for linked list */
void quickSortHelper(struct node *left, struct node *right) {
    if (right != NULL and left != right and left != right->next) {
        struct node *pivot = partition(left, right);
        quickSortHelper(left, pivot->prev);
        quickSortHelper(pivot->next, right);
    }
}
 
// The main function to sort a linked list. It mainly calls _quickSort()
void quickSort(struct node *head) {
    // Find last node
    struct node *right = lastNode(head);
 
    // Call the recursive QuickSort
    quickSortHelper(head, right);
}
 
 
// This function prints contents of linked list starting from the given node
void traverse(struct node *node) {
    struct node *last;
    printf("Traversal in forward direction \n");
    while (node != NULL) {
        printf("%d ", node->data);
        last = node;
        node = node->next;
    }
 
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf("%d ", last->data);
        last = last->prev;
    }
}