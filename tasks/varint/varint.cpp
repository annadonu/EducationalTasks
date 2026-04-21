#include "varint.h"

size_t decodeVarint(const uint8_t* data, size_t size, uint64_t& result)
{
    uint64_t currentResult = 0;
    uint8_t byte;
    uint64_t dataPart;
    const uint8_t dataMask = 0b01111111;
    const uint8_t msbMask = 0b10000000;
    uint64_t multiplier = 1;

    if(data == nullptr || size == 0 || size > 10)
        return 0;

    for(size_t i = 0; i < size; i++)
    {
        byte = data[i];
        dataPart = byte & dataMask;

        if(i == 9 && dataPart > 1)
            return 0;

        currentResult += dataPart * multiplier;
        multiplier *= 128;

        if((byte & msbMask) == 0)
        {
            result = currentResult;
            return i + 1;
        }
    }

    return 0;
}
