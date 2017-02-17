#ifndef stack_H
#define stack_H
 
#include <bits/stdc++.h>
 
template <typename T>
class stack {
 
    struct Node {
        T       data;
        Node*   next;
 
        Node(T const& data, Node* next)
            : data(data)
            , next(next) {
        }
 
        Node(T&& data, Node* next)
            : data(std::move(data))
            , next(next) {
        }
    };
 
public:
    ~stack();
    void push(T const& data);
    void push(T&& data);
    bool empty() const;
    int  size()  const;
    T    top()   const;
    void pop();
    void print(std::ostream& str = std::cout) const;
 
 
private:
    Node*   head     = nullptr;
    int     elements = 0;
};
 
template<typename T>
stack<T>::~stack() {
    Node* next;
    for(Node* loop = head; loop != nullptr; loop = next) {
        next = loop->next;
        delete loop;
    }
}
template<typename T>
void stack<T>::push(T const& data) {
    head = new Node(data, head);
    ++elements;
}
template<typename T>
void stack<T>::push(T&& data) {
    head = new Node(std::move(data), head);
    ++elements;
}
template<typename T>
bool stack<T>::empty() const {
    return head == nullptr;
}
template<typename T>
int stack<T>::size() const {
    return elements;
}
template<typename T>
T stack<T>::top() const {
    if (head == nullptr) {
        throw std::runtime_error("Invalid Action");
    }
    return head->data;
}
template<typename T>
void stack<T>::pop() {
    if (head == nullptr) {
        throw std::runtime_error("Invalid Action");
    }
    Node* tmp = head;
    head = head->next;
    --elements;
    delete tmp;
}
template<typename T>
void stack<T>::print(std::ostream& str) const {
    int id = 0;
    for(Node* loop = head; loop != nullptr; loop = loop->next, ++id) {
        str << "Element: " << id << "  = " << loop->data << "\n";
    }
}
 
#endif