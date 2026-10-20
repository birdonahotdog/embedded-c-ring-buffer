#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

#define TEST_CHECK(cond) do { \
    if (!(cond)) { \
        fprintf(stderr, "FAIL: %s:%d: %s\n", \
                __FILE__, __LINE__, #cond); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

int main(void)
{
    ring_buffer_t rb;
    uint8_t val = 0;

    ring_buffer_init(&rb);

    printf("[TEST 1] Initial state...\n");

    TEST_CHECK(ring_buffer_is_empty(&rb));
    TEST_CHECK(!ring_buffer_is_full(&rb));
    TEST_CHECK(ring_buffer_available(&rb) == 0);
    TEST_CHECK(ring_buffer_pop(&rb, &val) == RING_BUFFER_EMPTY);

    printf("[TEST 2] Capacity and overflow...\n");

    for (uint8_t i = 0; i < 63; i++) {
        TEST_CHECK(ring_buffer_push(&rb, i) == RING_BUFFER_OK);
        TEST_CHECK(ring_buffer_available(&rb) == (size_t)(i + 1));
    }

    TEST_CHECK(ring_buffer_is_full(&rb));
    TEST_CHECK(ring_buffer_push(&rb, 0xFF) == RING_BUFFER_FULL);

    printf("[TEST 3] FIFO ordering...\n");

    for (uint8_t i = 0; i < 63; i++) {
        TEST_CHECK(ring_buffer_pop(&rb, &val) == RING_BUFFER_OK);
        TEST_CHECK(val == i);
    }

    TEST_CHECK(ring_buffer_is_empty(&rb));
    TEST_CHECK(ring_buffer_available(&rb) == 0);

    printf("[TEST 4] Wrap-around...\n");

    for (int round = 0; round < 10; round++) {
        for (uint8_t i = 0; i < 40; i++) {
            uint8_t data = (uint8_t)(i + round * 10);
            TEST_CHECK(ring_buffer_push(&rb, data) == RING_BUFFER_OK);
        }

        for (uint8_t i = 0; i < 40; i++) {
            uint8_t expected = (uint8_t)(i + round * 10);

            TEST_CHECK(ring_buffer_pop(&rb, &val) == RING_BUFFER_OK);
            TEST_CHECK(val == expected);
        }
    }

    TEST_CHECK(ring_buffer_is_empty(&rb));

    printf("\nAll ring buffer tests passed!\n");
    return EXIT_SUCCESS;
}
