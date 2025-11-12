#include "file_analyzer.h"

bool file_analyzer_init(file_analyzer_ctx_t* ctx, 
                        double* max_deque_buffer,
                        double* min_deque_buffer,
                        double* window_deque_buffer,
                        uint16_t window_size) {
    if (!ctx || !max_deque_buffer || !min_deque_buffer || !window_deque_buffer || window_size == 0) {
        return false;
    }

    if (!static_double_deque_init(&ctx->max_deque, max_deque_buffer, window_size) ||
        !static_double_deque_init(&ctx->min_deque, min_deque_buffer, window_size) ||
        !static_double_deque_init(&ctx->window_deque, window_deque_buffer, window_size)) {
        return false;
    }

    ctx->window_sum = 0.0;
    ctx->window_size = window_size;

    return true;
}

bool file_analyzer_process_value(file_analyzer_ctx_t* ctx, double value, double* max, double* min, double* avg) {
}