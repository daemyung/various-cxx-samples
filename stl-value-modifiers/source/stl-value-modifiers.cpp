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

#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>

constexpr auto kTitleFieldWidth = 20;

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& data)
{
    for (auto i = 0; i != data.size() - 1; ++i)
        os << data[i] << ", ";

    os << data.back();

    return os;
}

class IdGenerator
{
public:
    IdGenerator()
        :
        m_id(0)
    {
    }

    int operator()()
    {
        return ++m_id;
    }

private:
    int m_id;
};

int getNewId()
{
    static int id = 0;
    return ++id;
}

int main(int argc, char* argv[])
{
    {
        std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::cout << std::setw(kTitleFieldWidth) << "Before fill: " << data << std::endl;

        std::fill(std::begin(data), std::end(data), 0);

        std::cout << std::setw(kTitleFieldWidth) << "After fill: " << data << std::endl;
    }

    {
        std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::cout << std::setw(kTitleFieldWidth) << "Before fill_n: " << data << std::endl;

        std::fill_n(std::begin(data), 5, 0);

        std::cout << std::setw(kTitleFieldWidth) << "After fill_n: " << data << std::endl;
    }

    {
        std::vector<int> data(9);

        std::cout << std::setw(kTitleFieldWidth) << "Before itoa: " << data << std::endl;

        std::iota(std::begin(data), std::end(data), 1);

        std::cout << std::setw(kTitleFieldWidth) << "After itoa: " << data << std::endl;
    }

    {
        std::vector<int> data(9);

        std::cout << std::setw(kTitleFieldWidth) << "Before generate: " << data << std::endl;

        std::generate(std::begin(data), std::end(data), IdGenerator());

        std::cout << std::setw(kTitleFieldWidth) << "After generate: " << data << std::endl;
    }

    {
        std::vector<int> data(9);

        std::cout << std::setw(kTitleFieldWidth) << "Before generate_n: " << data << std::endl;

        std::generate_n(std::begin(data), 5, IdGenerator());

        std::cout << std::setw(kTitleFieldWidth) << "After generate_n: " << data << std::endl;
    }

    {
        std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::cout << std::setw(kTitleFieldWidth) << "Before replace: " << data << std::endl;

        std::replace(std::begin(data), std::end(data), 9, 0);

        std::cout << std::setw(kTitleFieldWidth) << "After replace: " << data << std::endl;
    }

    {
        std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::cout << std::setw(kTitleFieldWidth) << "Before replace_if: " << data << std::endl;

        std::replace_if(std::begin(data), std::end(data), [](const int& v) { return v % 2; }, 0);

        std::cout << std::setw(kTitleFieldWidth) << "After replace_if: " << data << std::endl;
    }

    return 0;
}