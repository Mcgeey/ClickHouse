#include <IO/HashingWriteBuffer.h>
#include <IO/WriteBufferFromFile.h>

#define FAIL(msg) { std::cout << msg; exit(1); }


CityHash64_v1_0_2::uint128 referenceHash(const char * data, size_t len)
{
    const size_t block_size = DBMS_DEFAULT_HASHING_BLOCK_SIZE;
    CityHash64_v1_0_2::uint128 state(0, 0);
    size_t pos;

    for (pos = 0; pos + block_size <= len; pos += block_size)
    {
        state = CityHash64_v1_0_2::CityHash128WithSeed(data + pos, block_size, state);
    }

    if (pos < len)
        state = CityHash64_v1_0_2::CityHash128WithSeed(data + pos, len - pos, state);

    return state;
}
