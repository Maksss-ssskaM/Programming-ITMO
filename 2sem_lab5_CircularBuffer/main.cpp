#include <iostream>
#include <algorithm>
#include "CircularBuffer.h"
template <typename T>
void print(CircularBuffer<T>& buf)
{
    for (typename CircularBuffer<T>::Iterator iterator = buf.begin(); iterator != buf.end();
            ++iterator)
    {
        std::cout << *iterator << std::endl;;
    }
}
int main()
{
    CircularBuffer<int> buf(2);
    buf.addFirst(1);
    buf.addFirst(4);
    buf.addFirst(3);
    buf.addFirst(2);
    for (CircularBuffer<int>::Iterator i = buf.begin(); i < buf.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    buf.changeCapacity(5);
    buf.addLast(666);
    for (CircularBuffer<int>::Iterator i = buf.begin(); i < buf.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    buf.addByIndex(1, 9);
    for (CircularBuffer<int>::Iterator i = buf.begin(); i < buf.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    CircularBuffer<int>::Iterator it = std::find(buf.begin(), buf.end(), 1);
    it = std::max_element(buf.begin(), buf.end());
    std::cout << *it << std::endl;
    std::sort(buf.begin(), buf.end());
    for (CircularBuffer<int>::Iterator i = buf.begin(); i < buf.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}
