
#include "static_double_deque.h"
#include <stdio.h>
#include <assert.h>

#define TEST_QUEUE_SIZE 6

int main(int argc, const char *argv[]) {
  double buffer[TEST_QUEUE_SIZE];
  static_double_deque_t queue;

  assert(!static_double_deque_init(&queue, NULL, TEST_QUEUE_SIZE));
  assert(!static_double_deque_init(NULL, buffer, TEST_QUEUE_SIZE));

  assert(static_double_deque_init(&queue, buffer, TEST_QUEUE_SIZE));

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

  printf("All tests passed!\n");
}