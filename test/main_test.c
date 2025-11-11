
#include "static_double_deque.h"
#include <stdio.h>
#include <assert.h>

#define TEST_QUEUE_SIZE 6

void test_fill_and_empty_queue_front(void);
void test_fill_and_empty_queue_back(void);

int main(int argc, const char *argv[]) {
  test_fill_and_empty_queue_front();
  test_fill_and_empty_queue_back();

  printf("All tests passed!\n");
}
void test_fill_and_empty_queue_front(void) {
  printf("Test fill to max and empty all from front\n");
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
}

void test_fill_and_empty_queue_back(void) {
  printf("Test fill to max and empty all from back\n");
  double buffer[TEST_QUEUE_SIZE];
  static_double_deque_t queue;

  assert(!static_double_deque_init(&queue, NULL, TEST_QUEUE_SIZE));
  assert(!static_double_deque_init(NULL, buffer, TEST_QUEUE_SIZE));

  assert(static_double_deque_init(&queue, buffer, TEST_QUEUE_SIZE));

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