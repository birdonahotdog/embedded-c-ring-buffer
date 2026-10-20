# C11 Circular Ring Buffer

A fixed-capacity, byte-oriented circular ring buffer implemented in C11.

## Features

- Power-of-two capacity with bitmask-based index wrap-around.
- FIFO (First In, First Out) data handling.
- Explicit status codes for successful operations, full buffers, empty buffers, and null pointers.
- Fixed storage with no dynamic memory allocation.
- Unit tests for initialization, capacity, overflow, FIFO ordering, and wrap-around.

## Capacity

The buffer has 64 physical slots and can store up to 63 bytes at a time.
One slot is reserved to distinguish the full state from the empty state.

## Build and Run

Run `make test` to compile the code and execute the tests.
Run `make clean` to remove generated build files.

## Concurrency

Concurrent access from interrupts, tasks, or multiple cores has not been
validated. The use of `volatile` alone does not make this implementation
thread-safe or ISR-safe.
