#ifndef FILE_ANALYZER_H
#define FILE_ANALYZER_H

#include "static_double_deque.h"

typedef struct {
    static_double_deque_t max_deque;
    static_double_deque_t min_deque;
    static_double_deque_t window_deque;
    double window_sum;
    uint16_t window_size;
} file_analyzer_ctx_t;

bool file_analyzer_init(file_analyzer_ctx_t* ctx, 
                        double* max_deque_buffer,
                        double* min_deque_buffer,
                        double* window_deque_buffer,
                        uint16_t window_size);

bool file_analyzer_process_value(file_analyzer_ctx_t* ctx, double value, double* max, double* min, double* avg);

#endif