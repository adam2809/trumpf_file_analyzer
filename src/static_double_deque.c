#include "static_double_deque.h"
#include <stddef.h>

bool static_double_deque_init(static_double_deque_t* queue, double* buf, uint16_t max_size){
    if (queue == NULL || buf == NULL || max_size == 0) {
        return false;
    }
    queue->front_index = 0;
    queue->back_index = 0;
    queue->max_size = max_size;
    queue->size = 0;
    queue->buf = buf;
    return true;
}