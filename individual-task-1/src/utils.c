#include <stdarg.h>
#include "utils.h"

void free_many(int count, ...) {
  va_list args;
  va_start(args, count);
  for (unsigned int i = 0; i < count; i++) {
    void **ptr = va_arg(args, void**);
    free(*ptr);
    *ptr = NULL;
  }
  va_end(args);
}
