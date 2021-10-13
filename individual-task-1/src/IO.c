#include <stdlib.h>
#include "IO.h"
#include "utils.h"
#include "string.h"

#define BUFFER_SIZE 32

char *read_line(FILE *input) {
  RETURN_NULL_IF_NULL(input);
  char *result = NULL;
  size_t lastPaste = 0;
  char *process = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  FREE_RETURN_NULL(process, 1, &result);

  while (1) {
    int err = 1 - fscanf(input, "%"AS_STRING(BUFFER_SIZE)"s", process);
    if (err != 0) {
      fflush(input);
      free(process);
      free(result);
      return NULL;
    }

    size_t word_len = strlen(process);
    lastPaste += word_len;
    char *grown = realloc(result, lastPaste + 1);
    FREE_RETURN_NULL(grown, 2, &result, &process);
    result = grown;
    snprintf(result + lastPaste - word_len, word_len, "%s", process);

    char next = (char) fgetc(input);
    if (next == '\n' || next == EOF)
      break;
    else if (next == ' ' || next == '\t')
      result[lastPaste++] = next;
    else
      ungetc(next, input);
  }
  free(process);
  result[lastPaste] = '\0';
  return result;
}

char *read_word(FILE *input) {
  RETURN_NULL_IF_NULL(input);
  char *result = NULL;
  size_t lastPaste = 0;
  char *process = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  FREE_RETURN_NULL(process, 1, &result);

  while (1) {
    int err = 1 - fscanf(input, "%"AS_STRING(BUFFER_SIZE)"s", process);
    if (err != 0) {
      fflush(input);
      free(process);
      free(result);
      return NULL;
    }

    size_t word_len = strlen(process);
    lastPaste += word_len;
    char *grown = realloc(result, lastPaste + 1);
    FREE_RETURN_NULL(grown, 2, &result, &process);
    result = grown;
    snprintf(result + lastPaste - word_len, word_len, "%s", process);

    char next = (char) fgetc(input);
    if (next == '\n' || next == EOF || next == ' ' || next == '\t')
      break;
    else
      ungetc(next, input);
  }
  free(process);
  result[lastPaste] = '\0';
  return result;
}

int read_long(FILE *input, int64_t *out) {
  char *word = read_word(input), *end;
  RETURN_DEFAULT_IF_NULL(word, READ_ERROR);

  const int64_t result = strtol(word, &end, 10);
  if (word == end) {
    free(word);
    return PARSE_ERROR;
  }
  *out = result;
  free(word);
  return 0;
}
