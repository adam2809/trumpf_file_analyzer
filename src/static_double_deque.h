#ifndef STATIC_DOUBLE_DEQUE_H
#define STATIC_DOUBLE_DEQUE_H


#include <stdint.h>
#include <stdbool.h>

typedef struct static_double_deque_t {
    uint16_t front_index;
    uint16_t back_index;
    uint16_t max_size;
    double* buf;
} static_double_deque_t;

bool static_double_deque_init(static_double_deque_t* queue, double* buf, uint16_t max_size);
bool static_double_deque_push_front(static_double_deque_t* queue, double value);
bool static_double_deque_pop_front(static_double_deque_t* queue, double* value);
bool static_double_deque_push_back(static_double_deque_t* queue, double value);
bool static_double_deque_pop_back(static_double_deque_t* queue, double* value);
void print_queue(static_double_deque_t* queue);

#endif