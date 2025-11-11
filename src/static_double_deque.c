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

bool static_double_deque_push_front(static_double_deque_t* queue, double value){
    if (queue == NULL || queue->buf == NULL) {
        return false;
    }
    if ((queue->front_index + 1) % queue->max_size == queue->back_index) {
        return false; // Queue is full
    }

    if(queue->size > 0){
        queue->front_index = (queue->front_index + 1) % queue->max_size;
    }

    queue->size++;
    queue->buf[queue->front_index] = value;

    return true;
}