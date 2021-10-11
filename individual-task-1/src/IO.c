#include <stdlib.h>
#include "IO.h"
#include "utils.h"
#include "string.h"

#define BUFFER_SIZE 32

char *read_line(FILE *input) {
  RETURN_NULL_IF_NULL(input);
  char *result = NULL;
  size_t lastPaste = 0;

  while (1) {
    char *process = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    FREE_RETURN_NULL(process, 1, &result);

    int err = 1 - fscanf(input, "%"AS_STRING(BUFFER_SIZE)"s", process);
    if (err != 0) {
      free(process);
      free(result);
      return NULL;
    }

    size_t word_len = strlen(process);
    lastPaste += word_len;
    char *grown = realloc(result, lastPaste + 1);
    FREE_RETURN_NULL(grown, 2, &result, &process);
    result = grown;
    strcpy(result + lastPaste - word_len, process);
    free(process);

    char next = (char) fgetc(input);
    if (next == '\n' || next == EOF)
      break;
    else if (next == ' ' || next == '\t')
      result[lastPaste++] = next;
    else
      ungetc(next, input);
  }
  result[lastPaste] = '\0';
  return result;
}
