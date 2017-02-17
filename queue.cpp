#ifndef QUEUE_H
#define QUEUE_H
 
#include <iostream>
#include <stdexcept>
 
template <typename T>
class queue {
public:
    ~queue();
    bool empty() const;
    size_t size() const;
    T const& front() const;
    T& front();
    void push(T const& data);
    void push(T&& data);
    //void emplace (T&&... args);
    // void swap (queue& x);
    void pop();
 
private:
    size_t elements = 0;
    struct node {
        T data;
        node *next;
 
        node(T const& data, node* next)
            : data(data)
            , next(next) {
        }
 
        node(T&& data, node* next)
            : data(std::move(data))
            , next(next) {
        }
    };
    node *head = nullptr;
    node *tail = nullptr;
};
 
template <typename T>
queue<T>::~queue() {
    node *curr;
    while(head) {
        curr = head;
        head = head->next;
        delete curr;
    }
}
 
template <typename T>
bool queue<T>::empty() const {
    return elements == 0;
//    return head == nullptr;
}
 
template <typename T>
size_t queue<T>::size() const {
    return elements;
}
 
template <typename T>
T const& queue<T>::front() const {
    if(head == nullptr)
        throw std::runtime_error("Invalid Action");
    return head->data;
}
 
template <typename T>
T& queue<T>::front() {
    if(head == nullptr)
        throw std::runtime_error("Invalid Action");
    return head->data;
}
 
template <typename T>
void  queue<T>::push(T const& data) {
    node *newNode = new node(data, nullptr);
    if(head == nullptr) head = newNode;
    else tail->next = newNode;
    tail = newNode;
    ++elements;
}
template <typename T>
void  queue<T>::push(T&& data) {
    node *newNode = new node(std::move(data), nullptr);
    if(head == nullptr) head = newNode;
    else tail->next = newNode;
    tail = newNode;
    ++elements;
}
 
template <typename T>
void  queue<T>::pop() {
    if(head == nullptr)
        throw std::runtime_error("Invalid Action");
 
    node* remove = head;
    head = head->next;
    delete remove;
 
    --elements;
}
 
#endif // QUEUE_H