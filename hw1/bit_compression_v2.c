#include <stdint.h>
#include <stdio.h>

uint16_t count_leading_zeros(uint64_t x)
{
    for (int i = 1; i < 64; i = i << 1)
    {
        x |= (x >> i);
    }

    /* count ones (population count) */
    x -= ((x >> 1) & 0x5555555555555555 /* Fill this! */);
    x = ((x >> 2) & 0x3333333333333333) + (x & 0x3333333333333333 /* Fill this! */);
    x = ((x >> 4) + x) & 0x0f0f0f0f0f0f0f0f;
    x += (x >> 8);
    x += (x >> 16);
    x += (x >> 32);

    return (64 - (x & 0x7f));
}

uint32_t cvrt_uint32(uint64_t x)
{
    return (uint32_t)x;
}

uint16_t cvrt_uint16(uint64_t x)
{
    return (uint16_t)x;
}

int main()
{
    uint64_t test_data[3] = {0x0fffffffffffffff, 0x00003567, 0xa};
    uint16_t n;
    uint16_t bit_count = 64 * (sizeof(test_data) / 8), bit_reduced = 0;

    for (int i = 0; i < 3; i++)
        printf("%llu\n", test_data[i]);

    printf("original bit count: %hu\n", (unsigned short int)bit_count);
    bit_count = 0;
    for (int i = 0; i < 3; i++)
    {
        n = count_leading_zeros(test_data[i]);
        printf("leading zeros of test data[%d]: %hu\n", i, n);

        if (n >= 48)
        {
            uint16_t tmp_out = cvrt_uint16(test_data[i]);
            bit_count += 16;
            bit_reduced += 48;
        }
        else if (n >= 32)
        {
            uint32_t tmp_out = cvrt_uint32(test_data[i]);
            bit_count += 32;
            bit_reduced += 32;
        }
        else
            bit_count += 64;
    }
    printf("bit count after compressed: %hu\n", (unsigned short int)(bit_count));
    printf("bit reduced after compressed: %hu\n", (unsigned short int)(bit_reduced));
}
