template <class T>
class  Vector {
public:
 
    typedef T* iterator;
 
    Vector();
    Vector(size_t size);
    Vector(size_t size, const T & initial);
    Vector(const Vector<T>& v);
    ~Vector();
 
    Vector<T> & operator = (const Vector<T> &);
 
    size_t capacity() const;
    size_t size() const;
    bool empty() const;
 
    const iterator begin() const;
    iterator begin();
 
    const iterator end() const;
    iterator end();
 
    // both form should be implemented otherwise some STL functions won't work
    const T& front() const;
    T& front();
 
    const T& back() const;
    T& back();
 
    void push_back(const T& value);
    void pop_back();
 
    void reserve(size_t capacity);
    void resize(size_t size);
 
    T & operator[](size_t index) const;
 
    void clear();
private:
    size_t _size;
    size_t _capacity;
    T* buffer;
};
 
template<class T>
Vector<T>::Vector() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
}
 
template<class T>
Vector<T>::Vector(const Vector<T> & v) {
    _size = v._size;
    _capacity = v._capacity;
    buffer = new T[_size];
    copy(v.buffer, v.buffer + _size, buffer);
}
 
template<class T>
Vector<T>::Vector(size_t size) {
    _size = size;
    _capacity = size;
    buffer = new T[_capacity];
}
 
template <class T>
bool Vector<T>:: empty() const {
    return _size == 0;
}
 
template<class T>
Vector<T>::Vector(size_t size, const T& initial) {
    _size = size;
    _capacity = size;
    buffer = new T [_capacity];
    fill(buffer, buffer + _size, initial);
}
 
template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v) {
    free(buffer);
    _size = v._size;
    _capacity = v._capacity;
    buffer = new T [_capacity];
    copy(v.buffer, v.buffer + _size, buffer);
    return *this;
}
 
template<class T>
const typename Vector<T>::iterator Vector<T>::begin() const {
    return buffer;
}
 
template<class T>
typename Vector<T>::iterator Vector<T>::begin() {
    return buffer;
}
 
template<class T>
const typename Vector<T>::iterator Vector<T>::end() const {
    return buffer + _size;
}
 
template<class T>
typename Vector<T>::iterator Vector<T>::end() {
    return buffer + _size;
}
 
template<class T>
const T& Vector<T>::front() const {
    return buffer[0];
}
 
 
template<class T>
T& Vector<T>::front() {
    return buffer[0];
}
 
template<class T>
const T& Vector<T>::back() const {
    return buffer[_size - 1];
}
 
template<class T>
T& Vector<T>::back() {
    return buffer[_size - 1];
}
 
template<class T>
void Vector<T>::push_back(const T & v) {
    /*
        Incidentally, one common way of regrowing an array is to double the size as needed.
        This is so that if you are inserting n items at most only O(log n) regrowths are performed
        and at most O(n) space is wasted.
    */
    if (_size >= _capacity) {
        if(_capacity == 0)
            reserve(_capacity + 1);
        else
            reserve(_capacity * 2);
    }
    buffer [_size++] = v;
}
 
template<class T>
void Vector<T>::pop_back() {
    (reinterpret_cast<T*>(buffer)[_size - 1]).~T();
    _size--;
}
 
template<class T>
void Vector<T>::reserve(size_t capacity) {
    T* newBuffer = new T[capacity];
 
    copy(buffer, buffer + _size, newBuffer);
 
    _capacity = capacity;
    free(buffer);
    buffer = newBuffer;
}
 
template<class T>
size_t Vector<T>::size() const {
    return _size;
}
 
template<class T>
void Vector<T>::resize(size_t size) {
    reserve(size);
    _size = size;
}
 
template<class T>
T& Vector<T>::operator[](size_t index) const {
    return buffer[index];
}
 
template<class T>
size_t Vector<T>::capacity() const {
    return _capacity;
}
 
template<class T>
Vector<T>::~Vector() {
    free(buffer);
}