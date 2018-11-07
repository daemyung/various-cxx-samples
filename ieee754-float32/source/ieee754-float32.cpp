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
#include <cstdint>
#include <limits>

enum class FloatType
{
    POSTIVE_ZERO,
    NEGATIVE_ZERO,
    NORMALIZED_NUMBER,
    DENORMALIZED_NUMBER,
    POSTIVE_INFINITY,
    NEGATIVE_INFINITY,
    NOT_A_NUMBER
};

FloatType getFloatType(float value)
{
    static_assert(
        std::numeric_limits<float>::is_iec559 && (sizeof(float) == sizeof(uint32_t)),
        "Single precision IEEE754 floating point number has to be 32-bit."
    );

    // SIGN BIT | EXPONENT |        MANTISSA
    //     0    | 00000000 | 00000000000000000000000
    //
    //     EXAMPLE: -248.75
    // HEXADECIMAL: C3 78 C0 00 
    //
    // SIGN BIT | EXPONENT |        MANTISSA
    //     1    | 10000110 | 11110001100000000000000

    const auto BITS = *(reinterpret_cast<uint32_t*>(&value));

    const auto SIGN     = (BITS & 0x80000000) >> 31;
    const auto EXPONENT = (BITS & 0x7f800000) >> 23;
    const auto MANTISSA = (BITS & 0x007FFFFF) >> 0;

    if (0 == EXPONENT)
    {
        if (0 == MANTISSA)
        {
            return (0 == SIGN) ? FloatType::POSTIVE_ZERO : FloatType::NEGATIVE_ZERO;
        }
        else
        {
            return FloatType::DENORMALIZED_NUMBER;
        }
    }
    else if ((0x7f800000 >> 23) == EXPONENT)
    {
        if (0 == MANTISSA)
        {
            return (0 == SIGN) ? FloatType::POSTIVE_INFINITY : FloatType::NEGATIVE_INFINITY;
        }
        else
        {
            return FloatType::NOT_A_NUMBER;
        }
    }

    return FloatType::NORMALIZED_NUMBER;
}

void test(float value, FloatType floatType)
{
    assert(getFloatType(value) == floatType);
}


int main(int argc, char* argv[])
{
    static_assert(
        std::numeric_limits<float>::has_infinity,
        "IEEE754 requires infinity"
    );

    static_assert(
        std::numeric_limits<float>::has_quiet_NaN,
        "IEEE754 requires quite NaN"
    );

    static_assert(
        std::numeric_limits<float>::has_signaling_NaN,
        "IEEE754 requires signaling NaN"
    );

    test(+0.0f,                                        FloatType::POSTIVE_ZERO);
    test(-0.0f,                                        FloatType::NEGATIVE_ZERO);
    test( std::numeric_limits<float>::min(),           FloatType::NORMALIZED_NUMBER);
    test( std::numeric_limits<float>::max(),           FloatType::NORMALIZED_NUMBER);
    test( std::numeric_limits<float>::lowest(),        FloatType::NORMALIZED_NUMBER);
    test( std::numeric_limits<float>::quiet_NaN(),     FloatType::NOT_A_NUMBER);
    test( std::numeric_limits<float>::signaling_NaN(), FloatType::NOT_A_NUMBER);
    test(+std::numeric_limits<float>::infinity(),      FloatType::POSTIVE_INFINITY);
    test(-std::numeric_limits<float>::infinity(),      FloatType::NEGATIVE_INFINITY);
    test( std::numeric_limits<float>::denorm_min(),    FloatType::DENORMALIZED_NUMBER);

    return 0;
}