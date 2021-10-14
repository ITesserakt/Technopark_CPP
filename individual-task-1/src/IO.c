#include "IO.h"

#include <stdlib.h>

#include "string.h"
#include "utils.h"

#define BUFFER_SIZE 32
#define GROW_RATIO 2

char *read_line(FILE *input) {
  RETURN_NULL_IF_NULL(input);
  char *result = malloc(BUFFER_SIZE * sizeof(char));
  size_t length = 0;
  size_t capacity = BUFFER_SIZE;
  char process[BUFFER_SIZE];

  while (1) {
    int err = 1 - fscanf(input, "%" AS_STRING(BUFFER_SIZE) "s", process);
    if (err != 0) {
      free(result);
      return NULL;
    }

    size_t word_len = strlen(process);
    length += word_len;
    if (length == capacity) {
      char *grown = realloc(result, (capacity *= GROW_RATIO) * sizeof(char));
      FREE_RETURN_NULL(grown, 1, &result);
      result = grown;
    }
    strcpy(result + length - word_len, process);

    char next = (char)fgetc(input);
    if (next == '\n' || next == EOF)
      break;
    else if (next == ' ' || next == '\t')
      result[length++] = next;
    else
      ungetc(next, input);
  }
  result[length] = '\0';
  return result;
}

char *read_word(FILE *input) {
  RETURN_NULL_IF_NULL(input);
  char *result = malloc(BUFFER_SIZE * sizeof(char));
  size_t length = 0;
  size_t capacity = BUFFER_SIZE;
  char process[BUFFER_SIZE];

  while (1) {
    int err = 1 - fscanf(input, "%" AS_STRING(BUFFER_SIZE) "s", process);
    if (err != 0) {
      fflush(input);
      free(result);
      return NULL;
    }

    size_t word_len = strlen(process);
    length += word_len;
    if (length == capacity) {
      char *grown = realloc(result, (capacity *= GROW_RATIO) * sizeof(char));
      FREE_RETURN_NULL(grown, 1, &result);
      result = grown;
    }
    strcpy(result + length - word_len, process);

    char next = (char)fgetc(input);
    if (next == '\n' || next == EOF || next == ' ' || next == '\t')
      break;
    else
      ungetc(next, input);
  }
  result[length] = '\0';
  return result;
}

int read_long(FILE *input, long *out) {
  char *word = read_word(input), *end;
  RETURN_DEFAULT_IF_NULL(word, READ_ERROR);

  const long result = strtol(word, &end, 10);
  if (word == end) {
    free(word);
    return PARSE_ERROR;
  }
  *out = result;
  free(word);
  return 0;
}
