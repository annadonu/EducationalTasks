#include "fp16.h"
#include <cmath>

float convertFloat16ToFloat(uint16_t float16_bits)
{
    uint16_t signBit = float16_bits >> 15;
    uint16_t mantissa = (float16_bits & 0x3FF);
    uint16_t degree = (float16_bits >> 10) & 0x1F;
    float sign;
    float divider = std::pow(2.0f, 10);

    if(signBit == 0)
        sign = 1;
    else
        sign = -1;

    if(degree == 0)
        if(mantissa == 0)
            return sign * 0.0f;
        else
            return sign * std::pow(2.0f, -14) * (mantissa / divider);
    else if(degree == 31)
        if(mantissa == 0)
            return sign * INFINITY;
        else
            return NAN;
    else
        return sign * std::pow(2.0f, degree - 15) * (1 + (mantissa / divider));
}
