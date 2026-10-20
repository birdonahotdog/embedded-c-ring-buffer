#include "ring_buffer.h"
#include <assert.h>
#include <stdio.h>

void ring_buffer_init(ring_buffer_t *rb){
    assert(rb != NULL);
    rb->head = 0U;
    rb->tail = 0U;
}

bool ring_buffer_is_empty(const ring_buffer_t *rb){
    assert(rb != NULL);
    return (rb->head == rb->tail);
}

bool ring_buffer_is_full(const ring_buffer_t *rb){
    assert(rb != NULL);
    return (((rb->head + 1U) & RING_BUFFER_MASK) == rb->tail);
}

size_t ring_buffer_available(const ring_buffer_t *rb){
    assert(rb != NULL);
    return ((rb->head - rb->tail) & RING_BUFFER_MASK);
}

ring_buffer_status_t ring_buffer_push(ring_buffer_t *rb, uint8_t data){
    if (rb == NULL){
        return RING_BUFFER_NULL_PTR;
    }

    if (ring_buffer_is_full(rb) == true){
        return RING_BUFFER_FULL;
    }

    rb->buffer[rb->head] = data;
    rb->head = ((rb->head + 1U) & RING_BUFFER_MASK);
    return RING_BUFFER_OK;
}

ring_buffer_status_t ring_buffer_pop(ring_buffer_t *rb, uint8_t *data){
    if (rb == NULL || data == NULL){
        return RING_BUFFER_NULL_PTR;
    }

    if (ring_buffer_is_empty(rb) == true){
        return RING_BUFFER_EMPTY;
    }

    *data = rb->buffer[rb->tail];
    rb->tail = ((rb->tail + 1U) & RING_BUFFER_MASK);
    return RING_BUFFER_OK;
}
