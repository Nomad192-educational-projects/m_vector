#include <iostream>
#include "m_vector.h"

bool constructor_check();
bool get_set_check();
bool to_array_check();
bool operators_check();
bool iterators_check();

bool (*const checks[]) (void) = {constructor_check, get_set_check, to_array_check, operators_check, iterators_check};

int main()
{
    for(auto f : checks)
        if(f())
            return 1;


    m_vector <int> the_vector({-9, -8, -7, -6, -5, 3, 4, 6, 0});

    std::cout << "cout vec \"" << the_vector << "\"" << std::endl;
    std::cerr << "cerr vec \"" << the_vector << "\"" << std::endl;

    Iterator<int> it(the_vector);

    while(!it.is_end())
    {
        std::cout << *it << " ";
        ++it;
    }
    return 0;
}

bool constructor_check(){
    const int standard_length = 10;
    {//проверка конструктора длины
        m_vector <int> the_vector(standard_length);
        if(the_vector.get_length() != standard_length){
            std::cerr << "error length constructor, expected = " << standard_length << " length = " << the_vector.get_length() << std::endl;
            return true;
        }
    }
    {// отрицательная длина
        /*std::streambuf *buffer = std::cerr.rdbuf();
        std::cerr.rdbuf(nullptr);
        m_vector <int> the_vector(-standard_length);

        if(the_vector.get_length() != standard_length){
            std::cerr.rdbuf(buffer);
            std::cerr << "error negative length constructor, expected = " << standard_length << " length = " << the_vector.get_length() << std::endl;
            return true;
        }
        std::cerr.rdbuf(buffer);*/
    }
    {//конструктора копирования
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(the_vector_1);
        for(int i = 0; i < standard_length; i++){
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error copy constructor, expected = " << the_vector_1[i] << " value = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }
    {//конструктор инициализации
        m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
        if(the_vector.get_length() != 7){
            std::cerr << "error length constructor, expected = " << 7 << " length = " << the_vector.get_length() << std::endl;
            return true;
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            if(the_vector[i] != i - 3){
                std::cerr << "error copy constructor, expected = " << i - 3 << " value = " << the_vector[i] << std::endl;
                return true;
            }
        }
    }
    std::cout << "construct check passed" << std::endl;
    return false;
}

bool get_set_check(){
    {// get check
        m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector[i];
            if(value != i - 3){
                std::cerr << "error get[], expected = " << i - 3 << " value = " << value << std::endl;
                return true;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector.get_elem(i);
            if(value != i - 3){
                std::cerr << "error get(), expected = " << i - 3 << " value = " << value << std::endl;
                return true;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value1 = the_vector.get_elem(i);
            auto value2 = the_vector[i];
            if(value1 != value2){
                std::cerr << "error get() != get[], get() = " << value1 << " get[] = " << value2 << std::endl;
                return true;
            }
        }
        std::streambuf *buffer = std::cerr.rdbuf();
        std::cerr.rdbuf(nullptr);
        {
            auto value = the_vector.get_elem(-1);
            if(value != -3){
                std::cerr.rdbuf(buffer);
                std::cerr << "error get(-1), expected = " << -3 << " length = " << value << std::endl;
                return true;
            }
        }
        {
            auto value = the_vector.get_elem(the_vector.get_length());
            if(value != 3){
                std::cerr.rdbuf(buffer);
                std::cerr << "error get(len), expected = " << 3 << " length = " << value << std::endl;
                return true;
            }
        }
        {
            auto value = the_vector[-1];
            if(value != -3){
                std::cerr.rdbuf(buffer);
                std::cerr << "error get[-1], expected = " << -3 << " length = " << value << std::endl;
                return true;
            }
        }
        {
            auto value = the_vector[the_vector.get_length()];
            if(value != 3){
                std::cerr.rdbuf(buffer);
                std::cerr << "error get[len], expected = " << 3 << " length = " << value << std::endl;
                return true;
            }
        }
        std::cerr.rdbuf(buffer);
    }
    {// set check
        m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
        for (int i = 0; i < the_vector.get_length(); i++) {
            int diff = 20;
            auto pred_value = the_vector.get_elem(i) + diff;
            the_vector.set_elem(i, pred_value);  //non const
            auto post_value = the_vector.get_elem(i);
            if(post_value != pred_value){
                std::cerr << "error set(" << i << "), pred_get() + diff = " << pred_value << " post_get() = " << post_value << std::endl;
                return true;
            }
        }
        std::streambuf *buffer = std::cerr.rdbuf();
        std::cerr.rdbuf(nullptr);
        {
            int diff = 20;
            int i= -1;
            auto pred_value = the_vector.get_elem(i) + diff;
            the_vector.set_elem(i, pred_value);  //non const
            auto post_value = the_vector.get_elem(i);
            if(post_value != pred_value){
                std::cerr.rdbuf(buffer);
                std::cerr << "error set(" << i << "), pred_get() + diff = " << pred_value << " post_get() = " << post_value << std::endl;
                return true;
            }
        }
        {
            int diff = 20;
            int i= the_vector.get_length();
            auto pred_value = the_vector.get_elem(i) + diff;
            the_vector.set_elem(i, pred_value);  //non const
            auto post_value = the_vector.get_elem(i);
            if(post_value != pred_value){
                std::cerr.rdbuf(buffer);
                std::cerr << "error set(" << i << "), pred_get() + diff = " << pred_value << " post_get() = " << post_value << std::endl;
                return true;
            }
        }
        std::cerr.rdbuf(buffer);
    }
    std::cout << "get/set check passed" << std::endl;
    return false;
}
bool to_array_check()
{
    m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
    int *array = the_vector.to_array();
    for (int i  = 0; i < the_vector.get_length(); i++)
    {
        if(the_vector[i] != array[i])
        {
            std::cerr << "error to_array(), expected (" << i << ") = " << the_vector[i] << " val = " << array[i] << std::endl;
            return true;
        }
    }
    delete array;

    std::cout << "to_array check passed" << std::endl;
    return false;
}

bool operators_check() {
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;

        if(the_vector_1.get_length() != the_vector_2.get_length())
        {
            std::cerr << "error operator \"=\",  expected len = " << the_vector_1.get_length() << " len = " << the_vector_2.get_length() << std::endl;
            return true;
        }

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error operator \"=\",  expected val[" << i << "] = " << the_vector_1[i] << " val = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2;
        the_vector_3 += the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+=\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                return true;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2;
        the_vector_3 -= the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_2[i] - the_vector_1[i] ;
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"-=\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                return true;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;
        int multiplier = 5;
        the_vector_2 *= multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*=\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;
        int divider = 5;
        the_vector_2 /= divider;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] / divider;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"/=\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }

    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2 + the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                return true;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2 - the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_2[i] - the_vector_1[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"-\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                return true;
            }
        }
    }
    {
        int multiplier = 5;
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1 * multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }
    {
        int divider = 5;
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1 / divider;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] / divider;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"/\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                return true;
            }
        }
    }
    std::cout << "operators check passed" << std::endl;
    return false;
}

bool iterators_check()
{
    const int standard_length = 10;
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it = the_vector.iterator_begin();

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = it.value();
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator without overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                return true;
            }
            it.next();
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator without overload, it != iterator_end" << std::endl;
            return true;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator without overload, !it.is_end()" << std::endl;
            return true;
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it = the_vector.iterator_begin();

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = *it;
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator with overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                return true;
            }
            ++it;
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator with overload, it != iterator_end" << std::endl;
            return true;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator with overload, !it.is_end()" << std::endl;
            return true;
        }
    }
    std::cout << "iterators check passed" << std::endl;
    return false;
}