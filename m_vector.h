#ifndef M_VECTOR_H
#define M_VECTOR_H
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

#include "exception.h"
#define MIN(x, y) ((x) < (y) ? (x) : (y))

template<typename T>
class Iterator;

template <typename T>
class m_vector {
private:
    size_t n;
    T *data;

    void copy(T* arr);
public:
    m_vector();
    explicit m_vector(int length);
    m_vector(m_vector<T>const& vect);
    m_vector(std::initializer_list<T> lst);
    ~m_vector();

    m_vector<T>& operator =(m_vector lst);

    int get_length() const;
    void set_elem(int index, T& elem);
    T& get_elem(int index);
    T* to_array();
    T& operator[](int index);
    T& operator[](int index) const;
    m_vector<T>& operator +=(m_vector<T>& vect);
    m_vector<T>& operator -=(m_vector<T>& vect);
    m_vector<T>& operator *=(T const& val);
    m_vector<T>& operator /=(T const& val);

    Iterator<T> iterator_begin();
    Iterator<T> iterator_end();
};


template <typename T>
class Iterator {
private:
    size_t it;
    m_vector<T>& container_obj;
public:
    explicit Iterator<T>(m_vector<T> &container_obj);
    Iterator<T>(m_vector<T> *container_obj, size_t n);

    Iterator<T> next();
    bool is_end();
    T value();
    Iterator& operator ++();
    T& operator *();
    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
};

template <typename T>
void m_vector<T>::copy(T* arr){
    for(size_t i = 0; i < n; i++){
        data[i] = arr[i];
    }
}

template <typename T>
std::ostream& operator <<(std::ostream &os, m_vector <T> &lst){
    os << "m_vector(";
    size_t i = 0;
    for(; i < lst.get_length() - 1; i++){
        os << lst[i] << ", ";
    }
    os << lst[i] << ")";
    return os;
}

template <typename T>
m_vector<T>::m_vector() {
    size_t standard_length = 10;
    std::cerr << "standard length = " << standard_length << std::endl;
    n = standard_length;
    try {
       data = new T[n];
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
}

template <typename T>
m_vector<T>::m_vector(int length) {
    if(length <= 0){
        std::ostringstream os;
        os << "incorrect length = " << length << std::endl;
        std::string s = os.str();
        throw MException(s);
    }
    n = (size_t)length;
    try {
       data = new T[n];
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
}

template <typename T>
m_vector<T>::m_vector(m_vector<T>const& vector){
    n = vector.get_length();
    if(n == 0){
        throw MException("memory = 0, not good:(");
    }
    try {
       data = new T[n];
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
    copy(vector.data);
}

template <typename T>
m_vector<T>::m_vector(std::initializer_list<T> lst){
    //std::copy(lst.begin(), lst.end(), data);
    n = lst.size();
    if(n == 0){
        throw MException("memory = 0, not good:(");
    }
    try {
       data = new T[n];
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
    auto it = lst.begin();
    for(size_t i = 0; it != lst.end(); i++){
        data[i] = *it;
        it++;
    }
}

template <typename T>
m_vector<T>::~m_vector() {
    delete[] data;
}

template <typename T>
m_vector<T>& m_vector<T>::operator =(m_vector lst){
    if(this == &lst){
        return *this;
    }
    delete[] data;
    n = (size_t)lst.get_length();
    try {
       data = new T[n];
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
    copy(lst.data);
    return *this;
}

template <typename T>
T* m_vector<T>::to_array(){
    try {
       T *new_array = new T[n];
       for(size_t i = 0; i < n; i++){
           new_array[i] = data[i];
       }
       return new_array;
    } catch (std::bad_alloc &ex) {
        throw MException("not memory:(");
    }
}

template <typename T>
int m_vector<T>::get_length() const {
    return (int)n;
}

template <typename T>
T& m_vector<T>::operator[](int index) {
    if(index < 0){
        std::ostringstream os;
        os << "incorrect index - " << index <<  std::endl;
        std::string s = os.str();
        throw MException(s);
    }
    if(index >= n){     
        std::ostringstream os;
        os << "incorrect index - " << index << std::endl;
        std::string s = os.str();
        throw MException(s);
    }
    return data[index];
}


template <typename T>
T& m_vector<T>::operator[](int index) const{
    return (*this)[index];
}

template <typename T>
void m_vector<T>::set_elem(int index, T& elem){
    (*this)[index] = elem;
}

template <typename T>
T& m_vector<T>::get_elem(int index){
    return (*this)[index];
}

template <typename T>
m_vector<T>& m_vector<T>::operator +=(m_vector<T>& vect){
    for(size_t i = 0; i < MIN(n, vect.get_length()); i++){
        data[i] += vect[i];
    }
    return *this;
}

template <typename T>
m_vector<T>& m_vector<T>::operator -=(m_vector<T>& vect){
    for(size_t i = 0; i < MIN(n, vect.get_length()); i++){
        data[i] -= vect[i];
    }
    return *this;
}

template <typename T>
m_vector<T>& m_vector<T>::operator *=(T const& val){
    for(size_t i = 0; i < n; i++){
        data[i] *= val;
    }
    return *this;
}

template <typename T>
m_vector<T>& m_vector<T>::operator /=(T const& val){
    if(val == (T)0){
        throw MException("division by 0!");
    }else{
        for(size_t i = 0; i < n; i++){
            data[i] /= val;
        }
    }
    return *this;
}

template<typename T>
m_vector<T> operator +(m_vector<T>& v1, m_vector<T>& v2){
    m_vector<T> new_vector(v1);
    new_vector += v2;
    return new_vector;
}

template<typename T>
m_vector<T> operator -(m_vector<T>& v1, m_vector<T>& v2){
    m_vector<T> new_vector(v1);
    new_vector -= v2;
    return new_vector;
}

template<typename T>
m_vector<T> operator *(m_vector<T>& v1, T& val){
    m_vector<T> new_vector(v1);
    new_vector *= val;
    return new_vector;
}

template<typename T>
m_vector<T> operator /(m_vector<T>& v1, T& val){
    if(val == (T)0){
        throw MException("division by 0!");
    }else{
        m_vector<T> new_vector(v1);
        new_vector /= val;
        return new_vector;
    }
}

template<typename T>
Iterator<T> m_vector<T>::iterator_begin(){
    return Iterator<T>(this, 0);
}

template<typename T>
Iterator<T> m_vector<T>::iterator_end(){
    return Iterator<T>(this, n);
}


template<typename T>
Iterator<T>::Iterator(m_vector<T> &container_obj) : it{0}, container_obj{container_obj}{}

template<typename T>
Iterator<T>::Iterator(m_vector<T> *container_obj, size_t n) : it{n}, container_obj{*container_obj}{}

template<typename T>
Iterator<T> Iterator<T>::next(){
    return ++(*this);
}

template<typename T>
bool Iterator<T>::is_end(){
    return it == container_obj.get_length();
}

template<typename T>
T Iterator<T>::value(){
    return *(*this);
}

template<typename T>
Iterator<T>& Iterator<T>::operator ++(){
    if(!this->is_end()){
        it++;
    }
    return *this;
}

template<typename T>
T& Iterator<T>::operator *(){
     return container_obj[it];
}

template<typename T>
bool Iterator<T>::operator ==(Iterator<T> &b){
    return &container_obj == &b.container_obj && it == b.it;
}

template<typename T>
bool Iterator<T>::operator !=(Iterator<T> &b){
    return !((*this).operator ==(b));
}















#endif // M_VECTOR_H //защита от повторнго включения
