#ifndef VECTOR_M_VECTOR_H
#define VECTOR_M_VECTOR_H

#include <iostream>

template<typename T>
class Iterator;

template <typename T>
class m_vector
{
private:
    size_t n;
    T *data;

public:
    m_vector();
    m_vector(int length);
    m_vector(m_vector<T> &vect);
    m_vector(m_vector<T> const&vect);
    explicit m_vector(std::initializer_list<T> lst);
    ~m_vector();
    m_vector<T>& operator =( m_vector<T> const& lst);  ///m_vector const& lst
    int get_length() const;
    void set_elem(int index, T& elem);
    T& get_elem(int index);
    T* to_array();   ///Function cannot return array type 'T []'
    T& operator[](int index);
    T& operator[](int index) const;

    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, m_vector<_T>& lst);

    m_vector<T>& operator +=( m_vector<T>& vect);
    m_vector<T>& operator -=( m_vector<T>& vect);
    m_vector<T>& operator *=( T& val);
    m_vector<T>& operator /=( T& val);

    template<typename _T>
    friend m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2); ///зачем friend

    template<typename _T>
    friend m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2); ///зачем friend

    template<typename _T>
    friend m_vector<_T> operator *(m_vector<_T>& v1, _T& val);  ///зачем friend

    template<typename _T>
    friend m_vector<_T> operator /(m_vector<_T>& v1, _T& val);  ///зачем friend

    Iterator<T> iterator_begin();
    Iterator<T> iterator_end();
};

template<typename _T> std::ostream& operator <<(std::ostream& os, m_vector<_T>& lst)
{
    os << "m_vector(";
    size_t i = 0;
    for(; i < lst.get_length() - 1; i++)
        os << lst.data[i] << ", ";
    os << lst.data[i] << ")";
    return os;
}

template<typename _T> m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2)
{
    m_vector<_T> new_vector(v1);
    new_vector += v2;
    return new_vector;
}
template<typename _T> m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2)
{
    m_vector<_T> new_vector(v1);
    new_vector -= v2;
    return new_vector;
}
template<typename _T> m_vector<_T> operator *(m_vector<_T>& v1, _T& val)
{
    m_vector<_T> new_vector(v1);
    new_vector *= val;
    return new_vector;
}
template<typename _T> m_vector<_T> operator /(m_vector<_T>& v1, _T& val)
{
    m_vector<_T> new_vector(v1);
    new_vector /= val;
    return new_vector;
}

template<typename T>
class Iterator {
private:
    size_t i;
    m_vector<T> &container_obj;

public:
    Iterator<T>(m_vector<T> container_obj);
    Iterator<T>(m_vector<T> *container_obj, size_t n);
    Iterator<T> next();
    T value();
    bool is_end();
    Iterator &operator++();
    T &operator*();
    bool operator==(Iterator &b);
    bool operator!=(Iterator &b);
};


#endif //VECTOR_M_VECTOR_H
