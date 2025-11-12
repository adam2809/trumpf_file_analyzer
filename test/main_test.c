
#include "static_double_deque.h"
#include "file_analyzer.h"
#include <stdio.h>
#include <assert.h>


void test_fill_and_empty_queue_front(void);
void test_fill_and_empty_queue_back(void);
void test_queue_crossing_ring_buffer_seam(void);

#define DOUBLE_EPSILON 0.1
bool double_equals_close(double a, double b);
void test_file_analyzer_simple(void);

int main(int argc, const char *argv[]) {
  test_fill_and_empty_queue_front();
  test_fill_and_empty_queue_back();
  test_queue_crossing_ring_buffer_seam();
  test_file_analyzer_simple();


  printf("All tests passed!\n");
}
void test_fill_and_empty_queue_front(void) {
  printf("Test fill to max and empty all from front\n");
  int test_queue_size = 6;
  double buffer[test_queue_size];
  static_double_deque_t queue;

  assert(!static_double_deque_init(&queue, NULL, test_queue_size));
  assert(!static_double_deque_init(NULL, buffer, test_queue_size));

  assert(static_double_deque_init(&queue, buffer, test_queue_size));

  assert(queue.front_index == 0);
  assert(queue.back_index == 0);

  assert(static_double_deque_push_front(&queue, 1.1));
  assert(static_double_deque_push_front(&queue, 2.2));

  assert(buffer[queue.front_index] == 2.2);
  assert(buffer[queue.back_index] == 1.1);

  assert(static_double_deque_push_front(&queue, 3.3));
  assert(static_double_deque_push_front(&queue, 4.4));
  assert(static_double_deque_push_front(&queue, 5.5));
  assert(static_double_deque_push_front(&queue, 6.6));
  assert(!static_double_deque_push_front(&queue, 7.7));

  double value;
  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 6.6);
  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 5.5);
  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 4.4);
  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 3.3);

  assert(buffer[queue.front_index] == 2.2);
  assert(buffer[queue.back_index] == 1.1);

  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 2.2);

  assert(buffer[queue.front_index] == 1.1);
  assert(buffer[queue.back_index] == 1.1);

  assert(static_double_deque_pop_front(&queue, &value));
  assert(value == 1.1);
  assert(queue.size == 0);
  assert(queue.front_index == 0);
  assert(queue.back_index == 0);
}

void test_fill_and_empty_queue_back(void) {
  printf("Test fill to max and empty all from back\n");
  int test_queue_size = 6;
  double buffer[test_queue_size];
  static_double_deque_t queue;

  assert(!static_double_deque_init(&queue, NULL, test_queue_size));
  assert(!static_double_deque_init(NULL, buffer, test_queue_size));

  assert(static_double_deque_init(&queue, buffer, test_queue_size));

  assert(queue.front_index == 0);
  assert(queue.back_index == 0);

  assert(static_double_deque_push_back(&queue, 1.1));
  assert(static_double_deque_push_back(&queue, 2.2));

  assert(buffer[queue.back_index] == 2.2);
  assert(buffer[queue.front_index] == 1.1);

  assert(static_double_deque_push_back(&queue, 3.3));
  assert(static_double_deque_push_back(&queue, 4.4));
  assert(static_double_deque_push_back(&queue, 5.5));
  assert(static_double_deque_push_back(&queue, 6.6));
  assert(!static_double_deque_push_back(&queue, 7.7));

  double value;
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 6.6);
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 5.5);
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 4.4);
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 3.3);

  assert(buffer[queue.back_index] == 2.2);
  assert(buffer[queue.front_index] == 1.1);

  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 2.2);

  assert(buffer[queue.front_index] == 1.1);
  assert(buffer[queue.back_index] == 1.1);

  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 1.1);
  assert(queue.size == 0);
  assert(queue.front_index == 0);
  assert(queue.back_index == 0);
}

void test_queue_crossing_ring_buffer_seam(void){
  printf("Test popping and puhsing while crossing over ring buffer seam that the queue uses\n");

  int test_queue_size = 3;
  double buffer[test_queue_size];
  static_double_deque_t queue;

  assert(static_double_deque_init(&queue, buffer, test_queue_size));
  assert(static_double_deque_push_front(&queue, 1));
  assert(static_double_deque_push_front(&queue, 2));

  double value;
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 1);
  assert(queue.front_index == 1);
  assert(queue.back_index == 1);

  assert(static_double_deque_push_front(&queue, 3));
  assert(static_double_deque_push_front(&queue, 1));
  assert(!static_double_deque_push_front(&queue, 4));

  assert(queue.back_index == 1);
  assert(queue.front_index == 0);

  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 2);
  assert(static_double_deque_pop_back(&queue, &value));
  assert(value == 3);
  assert(static_double_deque_push_back(&queue, 4));

  assert(queue.back_index == 2);
  assert(queue.front_index == 0);
  assert(buffer[queue.back_index] == 4);
  assert(buffer[queue.front_index] == 1);
  assert(queue.size == 2);
}

bool double_equals_close(double a, double b){
  return (a - b < DOUBLE_EPSILON) && (b - a < DOUBLE_EPSILON);
}

void test_file_analyzer_simple(void){
  printf("Test file analyzer on simple example\n");

  int window_size = 3;
  double window_deque[window_size];
  double max_deque[window_size];
  double min_deque[window_size];

  file_analyzer_ctx_t ctx;

  assert(file_analyzer_init(
    &ctx, 
    (double*) &max_deque,
    (double*) &min_deque,
    (double*) &window_deque,
    window_size
  ));

  double max, min, avg;

  assert(file_analyzer_process_value(&ctx, 1.0, &max, &min, &avg));
  assert(double_equals_close(avg, 1.0));
  assert(double_equals_close(max, 1.0));
  assert(double_equals_close(min, 1.0));

  assert(file_analyzer_process_value(&ctx, 2.0, &max, &min, &avg));
  assert(double_equals_close(avg, 1.5));
  assert(double_equals_close(max, 2.0));
  assert(double_equals_close(min, 1.0));

  assert(file_analyzer_process_value(&ctx, 5.0, &max, &min, &avg));
  assert(double_equals_close(avg, 2.66));
  assert(double_equals_close(max, 5.0));
  assert(double_equals_close(min, 1.0));

  assert(file_analyzer_process_value(&ctx, 3.0, &max, &min, &avg));
  assert(double_equals_close(avg, 3.33));
  assert(double_equals_close(max, 5.0));
  assert(double_equals_close(min, 2.0));

  assert(file_analyzer_process_value(&ctx, 4.0, &max, &min, &avg));
  assert(double_equals_close(avg, 4.0));
  assert(double_equals_close(max, 5.0));
  assert(double_equals_close(min, 3.0));

  assert(file_analyzer_process_value(&ctx, 2.0, &max, &min, &avg));
  assert(double_equals_close(avg, 3.0));
  assert(double_equals_close(max, 4.0));
  assert(double_equals_close(min, 2.0));
}