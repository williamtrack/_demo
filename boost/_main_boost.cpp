// boost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING //�ɰ�boost c++17��������

#include <iostream>
#include "boost/circular_buffer.hpp"

#include <numeric>
#include <assert.h> //ֻ��debugģʽ����Ч



void test();
int main()
{
    std::byte a{ 0b1001 };
    //test();
    std::cout << "Hello World!\n";
    std::cout << std::to_integer<int>(a);
}

void test() {
    std::unique_ptr<boost::circular_buffer<std::byte>> bf = nullptr;

    // ����һ������Ϊ3��ѭ��������
    boost::circular_buffer<int> cb(3);

    // ����һЩԪ�ص�ѭ��������
    cb.push_back(1);
    cb.push_back(2);

    // ����
    assert(cb[0] == 1);
    assert(cb[1] == 2);
    assert(!cb.full());
    assert(cb.size() == 2);
    assert(cb.capacity() == 3);

    // �ٲ�������Ԫ��
    cb.push_back(3);
    cb.push_back(4);

    // ���
    int sum = std::accumulate(cb.begin(), cb.end(), 0);

    // ����
    assert(cb[0] == 2);
    assert(cb[1] == 3);
    assert(cb[2] == 4);
    assert(*cb.begin() == 2);
    assert(cb.front() == 2);
    assert(cb.back() == 4);
    assert(sum == 9);
    assert(cb.full());
    assert(cb.size() == 3);
    assert(cb.capacity() == 3);
}