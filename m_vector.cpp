#include "m_vector.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

template <typename T> m_vector<T>::m_vector() {
    size_t standard_length = 10;
    std::cerr << "standard length = " << standard_length << std::endl;
    n = standard_length;
    data = new T[n];
}
template <typename T> m_vector<T>::m_vector(int length) {
    if(length <= 0)
    {
        std::cerr << "incorrect length = " << length << " now length = " << abs(length) << std::endl;
        length = abs(length);
    }
    n = (size_t)length;
    data = new T[n];
}
template <typename T> m_vector<T>::m_vector(m_vector<T> &vect) : n{(size_t)vect.get_length()}, data(new T[n])
{
    for (size_t i = 0; i < n; i++)
    {
        data[i] = vect[i];
    }
}
template <typename T> m_vector<T>::m_vector(m_vector<T> const&vect) : n{(size_t)vect.get_length()}, data(new T[n])
{
    for (size_t i = 0; i < n; i++)
    {
        data[i] = vect[i];
    }
}
template <typename T> m_vector<T>::m_vector(std::initializer_list<T> lst) : n{lst.size()}, data(new T[n])
{
    //std::copy(lst.begin(), lst.end(), data);
    auto it = lst.begin();
    for(size_t i = 0; it != lst.end(); i++){
        data[i] = *it;
        it++;
    }
}
template <typename T> m_vector<T>::~m_vector()
{
    delete[] data;
}

template <typename T> m_vector<T>& m_vector<T>::operator =( m_vector<T> const& lst)
{  ///m_vector const& lst
    if(this == &lst)
        return *this;

    delete[] data;
    n = lst.get_length();
    data = new T[n];
    for(size_t i = 0; i < n; i++)
        data[i] = lst[i];
    return *this;
}
template <typename T> int m_vector<T>::get_length() const
{
    return (int)n;
}
template <typename T> void m_vector<T>::set_elem(int index, T& elem)
{
    //data[index] = elem;
    (*this)[index] = elem;
}
template <typename T> T&  m_vector<T>::get_elem(int index)
{
    //return data[index];
    return (*this)[index];
}
template <typename T> T* m_vector<T>::to_array()
{    ///Function cannot return array type 'T []'
    T *new_array = new T[n];
    for(size_t i = 0; i < get_length(); i++)
        new_array[i] = data[i];
    return new_array;
}

template <typename T> T& m_vector<T>::operator[](int index)
{
    if(index < 0){
        int standard_index = 0;
        std::cerr << "incorrect index - " << index << "standard index = " << standard_index << std::endl;
        index = standard_index;
    }
    if(index >= n){
        int standard_index = n - 1;
        std::cerr << "incorrect index - " << index << "standard index = " << standard_index << std::endl;
        index = standard_index;
    }
    return data[index];
}
template <typename T> T& m_vector<T>::operator[](int index) const
{
    /*if(index < 0){
        int standard_index = 0;
        std::cerr << "incorrect index - " << index << "standard index = " << standard_index << std::endl;
        index = standard_index;
    }
    if(index >= n){
        int standard_index = n - 1;
        std::cerr << "incorrect index - " << index << "standard index = " << standard_index << std::endl;
        index = standard_index;
    }
    return data[index];*/
    return (*this)[index];
}

template <typename T> m_vector<T>& m_vector<T>::operator +=( m_vector<T>& vect)
{
    for(size_t i = 0; i < MIN(this->get_length(), vect.get_length()); i++)
        data[i] += vect[i];
    return *this;
}
template <typename T> m_vector<T>& m_vector<T>::operator -=( m_vector<T>& vect)
{
    for(size_t i = 0; i < MIN(this->get_length(), vect.get_length()); i++)
        data[i] -= vect[i];
    return *this;
}
template <typename T> m_vector<T>& m_vector<T>::operator *=( T& val)
{
    for(size_t i = 0; i < this->get_length(); i++)
        data[i] *= val;
    return *this;
}
template <typename T> m_vector<T>& m_vector<T>::operator /=( T& val)
        {
    for (size_t i = 0; i < this->get_length(); i++)
        data[i] /= val;
    return *this;
}

template <typename T> Iterator<T> m_vector<T>::iterator_begin()
{
    return Iterator<T>(this, 0);
}
template <typename T> Iterator<T> m_vector<T>::iterator_end()
{
    return Iterator<T>(this, n);
}




template <typename T> Iterator<T>::Iterator(m_vector<T> container_obj) : i{0}, container_obj{container_obj} {}
template <typename T> Iterator<T>::Iterator(m_vector<T> *container_obj, size_t n) : i{n}, container_obj{*container_obj} {}

template <typename T> Iterator<T> Iterator<T>::next() {
    i++;
    return *this;
}
template <typename T> T Iterator<T>::value() {
    return container_obj[i];
}
template <typename T> Iterator<T>& Iterator<T>::operator++() {
    i++;
    return *this;
}
template <typename T> T& Iterator<T>::operator*() {
    return container_obj[i];
}
template <typename T> bool Iterator<T>::operator==(Iterator<T> &b) {
    return i == b.i && (&container_obj == &b.container_obj);
}
template <typename T> bool Iterator<T>::operator!=(Iterator<T> &b) {
    return !((*this) == b);
}
template <typename T> bool Iterator<T>::is_end()
{
    return i == container_obj.get_length();
}


template class m_vector<int>;
template class Iterator<int>;
