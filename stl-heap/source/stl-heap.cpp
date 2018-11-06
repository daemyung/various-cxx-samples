// MIT License
//
// Copyright(c) 2018 DAEMYUNG, JANG
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE

#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

constexpr auto kTitleFieldWidth = 25;

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& data)
{
    for (auto i = 0; i != data.size() - 1; ++i)
        os << data[i] << ", ";

    os << data.back();

    return os;
}

template <typename RandomIt>
void sortHeap(RandomIt first, RandomIt last)
{
    if (false == std::is_heap(first, last))
        std::make_heap(first, last);

    assert(true == std::is_heap(first, last));

    auto iter = last;
    do
    {
        std::pop_heap(first, iter);
        --iter;
    } while (iter != first);
}

int main(int argc, char* argv[])
{
    {
        std::vector<int> data = { 1, 1, 3, 4, 5 };
        assert(false == std::is_heap(std::begin(data), std::end(data)));

        std::cout << std::setw(kTitleFieldWidth) << "Before: " << data << std::endl;

        // Rearrange data to form the heap.
        //                      5
        //                     / \
        // 1, 1, 3, 4, 5 =>   4   3
        //                   / \
        //                  1   1
        std::make_heap(std::begin(data), std::end(data));
        assert(true == std::is_heap(std::begin(data), std::end(data)));

        std::cout << std::setw(kTitleFieldWidth) << "After: " << data << std::endl;

        // Push 9 into the heap.
        data.push_back(9);
        std::push_heap(std::begin(data), std::end(data));

        std::cout << std::setw(kTitleFieldWidth) << "After inserting 9: " << data << std::endl;

        // Push 2 into the heap.
        data.push_back(2);
        std::push_heap(std::begin(data), std::end(data));

        std::cout << std::setw(kTitleFieldWidth) << "After inserting 2: " << data << std::endl;

        // Pop the maximum value in the heap. This value is 9.
        std::pop_heap(std::begin(data), std::end(data));
        data.pop_back();

        std::cout << std::setw(kTitleFieldWidth) << "After popping: " << data << std::endl;

        // Pop the maximum value in the heap. This value is 5.
        std::pop_heap(std::begin(data), std::end(data));
        data.pop_back();

        std::cout << std::setw(kTitleFieldWidth) << "After popping: " << data << std::endl;
    }

    {
        std::vector<int> data = { 4, 8, 2, 1, 9, 5, 3 };

        // std::sort_heap assumes that data is arranged forming the heap.
        // Thus the data is rearranged to form the heap before calling std::sort_heap.
        std::make_heap(std::begin(data), std::end(data));
        std::sort_heap(std::begin(data), std::end(data));

        std::cout << std::setw(kTitleFieldWidth) << "Sort using std: " << data << std::endl;
    }

    {
        std::vector<int> data = { 4, 8, 2, 1, 9, 5, 3 };

        // Sort data using the heap sorting algorithm.
        sortHeap(std::begin(data), std::end(data));

        std::cout << std::setw(kTitleFieldWidth) << "Sort using custom: " << data << std::endl;
    }

    return 0;
}