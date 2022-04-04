#include <iostream>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

template<typename new_T>
class Iterator;

template <typename T>
class m_vector
{
private:
    size_t n;
    T *data;
    class Iterator<T> *it;

public:
    m_vector(std::initializer_list<T> lst) : n{lst.size()}, data(new T[n]), it{*this}
    {
        std::copy(lst.begin(), lst.end(), data);
    }

    Iterator<T> iterator_begin()
    {
        return *it;
    }

    Iterator<T> iterator_end()
    {
        return *it;
    }

    explicit m_vector(int length) : n{(size_t)length}, data(new T[n]), it{new Iterator<T>(*this)} {}

    m_vector(m_vector<T> &vect) : n{(size_t)vect.get_length()}, data(new T[n]), it{new Iterator<T>(*this)}
    {
        for (size_t i = 0; i < n; i++)
        {
            data[i] = vect[i];
        }
        //*this = vect;
    }
    ~m_vector()
    {
        delete[] data;
    }
    m_vector<T>& operator =( m_vector<T>& lst)  ///m_vector const& lst
    {
        if(this == &lst)
            return *this;

        delete[] data;
        data = new T[lst.get_length()];
        for(size_t i = 0; i < lst.get_length(); i++)
            data[i] = lst[i];
        return *this;
    }
    int get_length()
    {
        return (int)n;
    }
    T* to_array()   ///Function cannot return array type 'T []'
    {
        T *new_array = new T[n];
        for(size_t i = 0; i < get_length(); i++)
            new_array[i] = data[i];
        return new_array;
    }
    T& operator[](int index)
    {
        return data[(size_t)index];
    }

    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, m_vector<_T>& lst);

    m_vector<T>& operator +=( m_vector<T>& vect)
    {
        for(size_t i = 0; i < MIN(this->get_length(), vect.get_length()); i++)
            data[i] += vect[i];
        return *this;
    }
    m_vector<T>& operator -=( m_vector<T>& vect)
    {
        for(size_t i = 0; i < MIN(this->get_length(), vect.get_length()); i++)
            data[i] -= vect[i];
        return *this;
    }
    m_vector<T>& operator *=( T& val)
    {
        for(size_t i = 0; i < this->get_length(); i++)
            data[i] *= val;
        return *this;
    }
    m_vector<T>& operator /=( T& val)
    {
        for(size_t i = 0; i < this->get_length(); i++)
            data[i] /= val;
        return *this;
    }

    template<typename _T>
    friend m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2); ///зачем friend

    template<typename _T>
    friend m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2); ///зачем friend

    template<typename _T>
    friend m_vector<_T> operator *(m_vector<_T>& v1, _T& val);

    template<typename _T>
    friend m_vector<_T> operator /(m_vector<_T>& v1, _T& val);
};

template<typename _T>
std::ostream& operator <<(std::ostream& os, m_vector<_T>& lst)
{
    os << "m_vector(";
    size_t i = 0;
    for(; i < lst.get_length() - 1; i++)
        os << lst.data[i] << ", ";
    return os << lst.data[i] << ")";
    //return os;
}

template<typename _T>
m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2)
{
    m_vector<_T> new_vector(v1);
    new_vector += v2;
    return new_vector;
}

template<typename _T>
m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2)
{
    m_vector<_T> new_vector(v1);
    new_vector -= v2;
    return new_vector;
}

template<typename _T>
m_vector<_T> operator *(m_vector<_T>& v1, _T& val)
{
    m_vector<_T> new_vector(v1);
    new_vector *= val;
    return new_vector;
}

template<typename _T>
m_vector<_T> operator /(m_vector<_T>& v1, _T& val)
{
    m_vector<_T> new_vector(v1);
    new_vector /= val;
    return new_vector;
}

template<typename T>
class Iterator {
private:
    size_t i;
    m_vector<T> *container_obj;

public:
    Iterator<T>(m_vector<T> container_obj) : i{0}, container_obj{&container_obj} {}
    //Iterator(T *first) : cur {first} {}

    Iterator<T> next() {
        i++;
        return *this;
    }

    T value() {
        return (*container_obj)[i];
    }

    Iterator &operator++() {
        return next();
    }

    T &operator*() {
        return value();
    }

    bool operator==(Iterator &b) {
        return *this == b;
    }

    bool operator!=(Iterator &b) {
        return *this != b;
    }

    bool is_end()
    {
        return i == container_obj->get_length();
    }
};

int main() {
    m_vector<int> the_vector(10);
   // Iterator_LOL<int> the_iterator = the_vector.iterator_begin();

    //m_vector<int>::Iterator<int> the_iterator = the_vector.iterator_begin();
    //std::cout << the_iterator.value() << std::endl;

    std::cout << the_vector.get_length() << " " << the_vector << std::endl;
    std::cout << the_vector << std::endl;


    //Iterator<int> new_iterator(the_vector);
    Iterator<int> new_iterator = the_vector.iterator_begin();

    int i = 0;
    while(!new_iterator.is_end())
    {
        std::cout << i << " = " << new_iterator.value() << "\n";
        new_iterator.next();
        i++;
    }
    return 0;
}
