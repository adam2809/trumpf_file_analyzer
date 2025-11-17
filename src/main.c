#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "file_analyzer.h"

#define WINDOW_SIZE 500
#define MAX_DOUBLE_STR_LEN 24


double my_trunc(double x) {
    long long int_part = (long long)x;
    
    return (double)int_part;
}

void make_double_str(double value, char* buffer) {
  sprintf(buffer,"%.2f", my_trunc(value * 100) / 100);
}

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

  FILE* input_file_fp = fopen(input_file_dir, "r");
  if(input_file_fp == NULL) {
    printf("ERROR! Could not open input file\n");
    return 1;
  }
  FILE* output_file_fp = fopen(output_file_dir, "w");
  if(output_file_fp == NULL) {
    printf("ERROR! Could not open output file\n");
    return 1;
  }

  char* input_line = NULL;
  size_t input_line_len = 0;

  char* output_header_line = "Wejście;Avg;Max;Min\n";
  fwrite(output_header_line, sizeof(char), strlen(output_header_line), output_file_fp);
  if(getline(&input_line, &input_line_len,input_file_fp) == -1) {
    goto exit;
  }

  while(getline(&input_line, &input_line_len,input_file_fp) != -1) {
    int carrige_return_index = strcspn(input_line, "\r");
    if(carrige_return_index < strlen(input_line)) {
      input_line[carrige_return_index] = '\0';
    }else{
      input_line[strcspn(input_line, "\n")] = '\0';
    }

    double value = strtod(input_line, &endptr);
    if (*endptr != '\0') {
      printf("ERROR! A sample in the input file (%s) cannot be interpreted as a number\n", input_line);
      return 1;
    }

    double max, min, avg;

    if(!file_analyzer_process_value(&ctx, value, &max, &min, &avg)) {
      printf("ERROR! Could not process value\n");
      return 1;
    }
    char output_line[MAX_DOUBLE_STR_LEN*4 + 4];
    char value_str[MAX_DOUBLE_STR_LEN];
    char avg_str[MAX_DOUBLE_STR_LEN];
    char min_str[MAX_DOUBLE_STR_LEN];
    char max_str[MAX_DOUBLE_STR_LEN];

    make_double_str(value, value_str);
    make_double_str(avg, avg_str);
    make_double_str(min, min_str);
    make_double_str(max, max_str);

    int written_chars = snprintf(output_line, sizeof(output_line), "%s;%s;%s;%s\n",value_str ,avg_str, max_str, min_str);
    fwrite(output_line, sizeof(char), written_chars, output_file_fp);
    if(ferror(output_file_fp)) {
      printf("ERROR! Could not write to output file\n");
      free(input_line);
      fclose(input_file_fp);
      return 1;
    }
  }

exit:

  if(errno != 0) {
    printf("ERROR! An error occurred while reading the file\n");
    return 1;
  }else{
    printf("Processing completed successfully\n");
    return 0;
  }

  free(input_line);
  fclose(input_file_fp);
}
