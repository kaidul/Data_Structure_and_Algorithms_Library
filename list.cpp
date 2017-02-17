#ifndef list_H
#define list_H
 
#include <iostream>
#include <stdexcept>
 
template <typename T>
class list {
public:
    // Rule of three
    list();
    list(list<T> const &);
    list(list<T> &&);
    list <T> & operator = (list<T> );
    list <T> & operator = (list<T> &&);
    ~list();
 
    /* Modifiers */
    void push_back(T&& data);
    void push_back(T const& data);
 
    void push_front(T&& data);
    void push_front(T const& data);
 
    void pop_back();
    void pop_front();
    void swap(list &x);
    void clear();
 
    /* Capacity */
    size_t size() const;
    bool empty() const;
 
    /* Element Access */
    T& front();
    T const& front() const;
 
    T& back();
    T const& back() const;
 
    /* Iterators */
    /*
    pointers doesn't suffice as iterators since the steps from an object to it's adjacent objects is not as easy as an increase / decrease of the adress. You have to access the underlying nodes next and prev pointers. Hence the iterator type must an own class.
    */
 
//    typedef T* iterator;
//    typedef T const* const_iterator;
//    typedef T* reverse_iterator;
//    typedef T const* const_reverse_iterator;
 
//    const_iterator begin() const; // cbegin
//    iterator begin();
//
//    const_iterator end() const; //cend()
//    iterator end();
//
//    const_reverse_iterator rbegin() const;
//    reverse_iterator rbegin();
//
//    const_reverse_iterator rend() const;
//    reverse_iterator rend();
 
private:
    struct node {
        int data;
        node *next, *prev;
        node(T const& data, node* next, node* prev)
            : data(data)
            , next(next)
            , prev(prev) {
        }
        node(T&& data, node* next, node* prev)
            : data(std::move(data))
            , next(next)
            , prev(prev) {
        }
    };
    int elements;
    node *head, *tail;
};
 
// empty constructor
template <typename T>
list<T>::list() {
    elements = 0;
    head = tail = nullptr;
}
 
// destructor
template <typename T>
list <T>::~list() {
    node* tmp;
    while(head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
 
template <typename T>
void list<T>::swap(list &that) {
    std::swap(head, that.head);
    std::swap(tail, that.tail);
    std::swap(elements, that.elements);
}
 
/* Copy assignment operator */
template <typename T>
list<T>& list<T>::operator = (list<T> rhs) {
    // copy and swap idiom 
    this->swap(rhs);
}
 
/* Move assignment operator */
template <typename T>
list<T>& list<T>::operator = (list<T> &&rhs) {
    this->swap(rhs);
}
 
/* Copy contructor */
template <typename T>
list<T>::list(list<T> const& rhs)
    : elements(rhs.size()) {
    if(!rhs.empty()) {
        node* rhsIt = rhs.head;
        node* It = new node(rhsIt->data, nullptr, nullptr);
        head = It;
        while((rhsIt = rhsIt->next) != rhs.tail) {
            try {
                node* Next = new node(rhsIt->data, It, nullptr);
                It = It->next = Next;
            } catch(std::bad_alloc& Exception) {
                /* if bad allocation occur, then delete all the already allocated node */
                for(node* Last; head != nullptr; delete Last) {
                    Last = head;
                    head = head->next;
                }
                throw;
            }
        }
        tail = It;
        tail->next = nullptr;
    }
}
 
template <typename T>
T& list<T>:: front() {
    if(head == nullptr)
        throw std::runtime_error("Invalid Action!");
    return head->data;
}
 
template <typename T>
T& list<T>:: back() {
    if(tail == nullptr)
        throw std::runtime_error("Invalid Action!");
    return tail->data;
}
 
template <typename T>
void list<T>::push_back(T const& data) {
    node* newNode = new node(data, nullptr, tail);
    if(head == nullptr)
        head = newNode;
    if(tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}
 
template <typename T>
void list<T>::push_back(T&& data) {
    node* newNode = new node(std::move(data), nullptr, tail);
    if(head == nullptr)
        head = newNode;
    if(tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    ++elements;
}
 
template <typename T>
void list<T>::push_front(T const& data) {
    node* newNode = new node(data, head, nullptr);
    if(tail == nullptr)
        tail = newNode;
    if(head != nullptr)
        head->prev = newNode;
    head = newNode;
    ++elements;
}
 
template <typename T>
void list<T>::push_front(T&& data) {
    node* newNode = new node(std::move(data), head, nullptr);
    if(tail == nullptr)
        tail = newNode;
    if(head != nullptr)
        head->prev = newNode;
    head = newNode;
    ++elements;
}
 
template <typename T>
void list<T>::pop_front() {
    if(head == nullptr)
        throw std::runtime_error("Invalid Action");
    node *tmp = head;
    head = head->next;
    if(head != nullptr)
        head->prev = nullptr;
    --elements;
    if(elements == 0)
        tail = nullptr;
    delete tmp;
}
 
template <typename T>
void list<T>::pop_back() {
    if(tail == nullptr)
        throw std::runtime_error("Invalid Action");
    node *tmp = tail;
    tail = tail->prev;
    if(tail != nullptr)
        tail->next = nullptr;
    --elements;
    if(elements == 0)
        head = nullptr;
    delete tmp;
}
 
template <typename T>
bool list<T>::empty() const {
    return head == nullptr;
}
 
template <typename T>
size_t list<T>::size() const {
    return elements;
}
 
template <typename T>
void list<T>::clear() {
    node* curr = head;
    while(head) {
        curr = head;
        head = head->next;
        delete curr;
    }
    head = tail = nullptr;
    elements = 0;
}
 
#endif // list_H