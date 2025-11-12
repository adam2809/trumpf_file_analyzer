#include "file_analyzer.h"
#include <stddef.h>


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
    if (!ctx || !max || !min || !avg) {
        return false;
    }

    double prev;
    double ret;
    if(ctx->window_deque.size == ctx->window_size) {
        static_double_deque_pop_back(&ctx->window_deque, &prev);
        ctx->window_sum -= prev;
    }
        
    static_double_deque_push_front(&ctx->window_deque, value);
    ctx->window_sum += value;

    *avg = ctx->window_sum / ctx->window_deque.size;

    if(static_double_deque_peek_front(&ctx->max_deque, &ret) && ret == prev) {
        static_double_deque_pop_front(&ctx->max_deque, NULL);
    }

    while(static_double_deque_peek_back(&ctx->max_deque, &ret) && ret < value) {
        static_double_deque_pop_back(&ctx->max_deque, NULL);
    }

    static_double_deque_push_back(&ctx->max_deque, value);

    if(static_double_deque_peek_front(&ctx->max_deque, &ret)) {
        *max = ret;
    }else{
        return false;
    }
    print_queue(&ctx->max_deque);

    return true;
}