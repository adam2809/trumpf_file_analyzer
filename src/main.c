#include <stdio.h>
#include <stdlib.h>

#include "file_analyzer.h"

#define WINDOW_SIZE 500
#define MAX_DOUBLE_STR_LEN 24


int main(int argc, const char *argv[]) {
  if(argc != 4) {
    printf("ERROR! Wrong arguments count. This program takes the input file directory as the first argument, output file directory as the second and window size as third\n");
    return 1;
  }

  char *endptr;
  uint16_t window_size = strtol((char *) argv[3], &endptr, 10);
  if (*endptr != '\0') {
    printf("ERROR! The provided window size in first argument is not a number\n");
    return 1;
  }

  char* input_file_dir = (char *)argv[1];
  char* output_file_dir = (char *)argv[2];

  file_analyzer_ctx_t ctx;
  double max_deque_buffer[WINDOW_SIZE];
  double min_deque_buffer[WINDOW_SIZE];
  double window_deque_buffer[WINDOW_SIZE];
  if(!file_analyzer_init(&ctx, max_deque_buffer, min_deque_buffer, window_deque_buffer, window_size)) {
    printf("ERROR! Could not initialize file analyzer\n");
    return 1;
  }
}
