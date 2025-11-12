#include "file_analyzer.h"
#include <stddef.h>

bool update_extremes_sliding_window(static_double_deque_t* deque, double value, double prev, bool is_prev , double* new_min_max, bool is_max){
    double ret;

    if(static_double_deque_peek_front(deque, &ret) && is_prev && ret == prev) {
        static_double_deque_pop_front(deque, NULL);
    }

    while(static_double_deque_peek_back(deque, &ret) && (is_max ? ret < value : ret > value)) {
        static_double_deque_pop_back(deque, NULL);
    }

    static_double_deque_push_back(deque, value);

    if(static_double_deque_peek_front(deque, &ret)) {
        *new_min_max = ret;
    }else{
        return false;
    }

    return true;
}

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
    bool is_prev = false;
    if(ctx->window_deque.size == ctx->window_size) {
        is_prev = true;
        static_double_deque_pop_back(&ctx->window_deque, &prev);
        ctx->window_sum -= prev;
    }
        
    static_double_deque_push_front(&ctx->window_deque, value);
    ctx->window_sum += value;

    *avg = ctx->window_sum / ctx->window_deque.size;

    return update_extremes_sliding_window(&ctx->max_deque, value, prev,is_prev, max, true) && update_extremes_sliding_window(&ctx->min_deque, value, prev,is_prev, min, false);
}