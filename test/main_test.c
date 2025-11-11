
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

  printf("All tests passed!\n");
}