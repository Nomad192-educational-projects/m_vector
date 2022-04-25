#include <iostream>
#include "exception.h"
#include "m_vector.h"

bool constructor_check();
bool get_set_check();
bool to_array_check();
bool operators_check();
bool iterators_check();

void check_construct_ini            (bool &success);
void check_get                      (bool &success);
void check_get_err                  (bool &success);
void check_set_and_err              (bool &success);
void check_math_operation_add_sub_eq(bool &success);
void check_math_operation_mul_dvd_eq(bool &success);
void check_math_operation_add_sub   (bool &success);
void check_math_operation_mul_dvd   (bool &success);


bool (*const checks[])(void) = {constructor_check, get_set_check, to_array_check, operators_check, iterators_check};

int main() {
    for(auto f : checks)
           if(!f())
               return 1;
    return 0;
}

bool constructor_check(){
    bool success = true;
    const int standard_length = 10;
    {
        m_vector <int> the_vector(standard_length);
        if(the_vector.get_length() != standard_length){
            success = false;
            std::cerr << "error length constructor, expected = " << standard_length << " length = " << the_vector.get_length() << std::endl;
        }
    }
    {
        try {
            m_vector <int> the_vector(-standard_length);
            success = false;
            std::cerr << "error length constructor, expected error, length = " << -standard_length << std::endl;
        } catch (MException &ex) {}
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(the_vector_1);
        for(int i = 0; i < standard_length; i++){
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error copy constructor, expected = " << the_vector_1[i] << " value = " << the_vector_2[i] << std::endl;
                success = false;
            }
        }
    }
    check_construct_ini(success);
    std::cout << (success ? "construct check passed" : "construct check not passed") << std::endl;
    return success;
}
void check_construct_ini(bool &success){
    {
        m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
        if(the_vector.get_length() != 7){
            std::cerr << "error ini constructor, expected = " << 7 << " length = " << the_vector.get_length() << std::endl;
            success = false;
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            if(the_vector[i] != i - 3){
                std::cerr << "error ini constructor, expected = " << i - 3 << " value = " << the_vector[i] << std::endl;
                success = false;
            }
        }
        try {
            m_vector <int> the_vector_2({});
            std::cerr << "error ini constructor, expected error, length = " << 0 << std::endl;
            success = false;
        }  catch (MException &ex) {

        }
    }
}


bool get_set_check(){
    bool success = true;
    check_get(success);
    check_get_err(success);
    check_set_and_err(success);

    std::cout << (success ? "get/set check passed" : "get/set check not passed") << std::endl;
    return success;
}


bool to_array_check()
{
    bool success = true;
    m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
    int *array = the_vector.to_array();
    for (int i  = 0; i < the_vector.get_length(); i++)
    {
        if(the_vector[i] != array[i])
        {
            std::cerr << "error to_array(), expected (" << i << ") = " << the_vector[i] << " val = " << array[i] << std::endl;
            success = false;
        }
    }
    delete[] array;
    std::cout << (success ? "to array check passed" : "to array check not passed") << std::endl;
    return success;
}

bool operators_check() {
    bool success = true;
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        the_vector_2 = the_vector_1;

        if(the_vector_1.get_length() != the_vector_2.get_length())
        {
            std::cerr << "error operator \"=\",  expected len = " << the_vector_1.get_length() << " len = " << the_vector_2.get_length() << std::endl;
            success = false;
        }

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error operator \"=\",  expected val[" << i << "] = " << the_vector_1[i] << " val = " << the_vector_2[i] << std::endl;
                success = false;
            }
        }
    }

    check_math_operation_add_sub_eq(success);
    check_math_operation_mul_dvd_eq(success);
    check_math_operation_add_sub(success);
    check_math_operation_mul_dvd(success);

    std::cout << (success ? "operators check passed" : "operators check not passed") << std::endl;
    return success;
}

bool iterators_check()
{
    bool success = true;
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
                success = false;
            }
            it.next();
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator without overload, it != iterator_end" << std::endl;
            success = false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator without overload, !it.is_end()" << std::endl;
            success = false;
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
                success = false;
            }
            ++it;
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator with overload, it != iterator_end" << std::endl;
            success = false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator with overload, !it.is_end()" << std::endl;
            success = false;
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it(the_vector);

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = *it;
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator with overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                success = false;
            }
            ++it;
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator with overload, it != iterator_end" << std::endl;
            success = false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator with overload, !it.is_end()" << std::endl;
            success = false;
        }
    }
    std::cout << (success ? "iterators check passed" : "iterators check not passed") << std::endl;
    return success;
}

void check_get(bool &success){
    m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
    {// get check
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector[i];
            if(value != i - 3){
                std::cerr << "error get[], expected = " << i - 3 << " value = " << value << std::endl;
                success = false;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector.get_elem(i);
            if(value != i - 3){
                std::cerr << "error get(), expected = " << i - 3 << " value = " << value << std::endl;
                success = false;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value1 = the_vector.get_elem(i);
            auto value2 = the_vector[i];
            if(value1 != value2){
                std::cerr << "error get() != get[], get() = " << value1 << " get[] = " << value2 << std::endl;
                success = false;
            }
        }

    }
}

void check_get_err(bool &success){
    m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
    {
        try {
            the_vector.get_elem(-1);
            std::cerr << "error get(-1), expected error " << std::endl;
            success = false;
        }  catch (MException &ex) {}
    }
    {
        try {
            the_vector.get_elem(the_vector.get_length());
            std::cerr << "error get(len), expected error " << std::endl;
            success = false;
        }  catch (MException &ex) {}

    }
    {
        try {
            the_vector[-1];
            std::cerr << "error get[-1], expected error" << std::endl;
            success = false;
        }  catch (MException &ex) {}
    }
    {
        try {
            the_vector[the_vector.get_length()];
            std::cerr << "error get[len], expected error" << std::endl;
            success = false;
        }  catch (MException &ex) {

        }
    }
}

void check_set_and_err(bool &success){
    {//set check
        m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
        for (int i = 0; i < the_vector.get_length(); i++) {
            int diff = 20;
            auto pred_value = the_vector.get_elem(i) + diff;
            the_vector.set_elem(i, pred_value);  //non const
            auto post_value = the_vector.get_elem(i);
            if(post_value != pred_value){
                std::cerr << "error set(" << i << "), pred_get() + diff = " << pred_value << " post_get() = " << post_value << std::endl;
                success = false;
            }
        }
        {
            try {
                int value = 0;
                the_vector.set_elem(-1, value);
                std::cerr << "error set(-1), expected error " << std::endl;
                success = false;
            }  catch (MException &ex) {}
        }
        {
            try {
                int value = 0;
                the_vector.set_elem(the_vector.get_length(), value);
                std::cerr << "error set(len), expected error " << std::endl;
                success = false;
            }  catch (MException &ex) {}
        }
    }
}

void check_math_operation_add_sub_eq(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2;
        the_vector_3 += the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+=\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = false;
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
                success = false;
            }
        }
    }
}

void check_math_operation_mul_dvd_eq(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;
        int multiplier = 5;
        the_vector_2 *= multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*=\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = false;
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
                success = false;
            }
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        try {
            the_vector /= 0;
            std::cerr << "error operator \"/=\",  expected error " << std::endl;
            success = false;
        }  catch (MException &ex) {

        }
    }
}

void check_math_operation_add_sub(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2 + the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = false;
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
                success = false;
            }
        }
    }
}

void check_math_operation_mul_dvd(bool &success){
    const int standard_length = 10;
    {
        int multiplier = 5;
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1 * multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = false;
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
                success = false;
            }
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        int divider = 0;
        try {
            the_vector / divider;
            std::cerr << "error operator \"/\",  expected error " << std::endl;
            success = false;
        }  catch (MException &ex) {

        }
    }
}







