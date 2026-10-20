#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define RING_BUFFER_CAPACITY 64U
#define RING_BUFFER_MASK     (RING_BUFFER_CAPACITY - 1U)

// Compile-time sanity check: CAPACITY must be a power of two
_Static_assert((RING_BUFFER_CAPACITY & RING_BUFFER_MASK) == 0, 
               "RING_BUFFER_CAPACITY must be a power of two!");

typedef enum {
    RING_BUFFER_OK = 0,
    RING_BUFFER_EMPTY,
    RING_BUFFER_FULL,
    RING_BUFFER_NULL_PTR
} ring_buffer_status_t;

typedef struct {
    uint8_t buffer[RING_BUFFER_CAPACITY];
    volatile uint32_t head;  // Producer write index
    volatile uint32_t tail;  // Consumer read index
} ring_buffer_t;

// API Declarations
void ring_buffer_init(ring_buffer_t *rb);
bool ring_buffer_is_empty(const ring_buffer_t *rb);
bool ring_buffer_is_full(const ring_buffer_t *rb);
size_t ring_buffer_available(const ring_buffer_t *rb);

ring_buffer_status_t ring_buffer_push(ring_buffer_t *rb, uint8_t data);
ring_buffer_status_t ring_buffer_pop(ring_buffer_t *rb, uint8_t *data);

#endif
