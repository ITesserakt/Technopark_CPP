#pragma once

#include <stdlib.h>
#include <stdio.h>

#define AS_STRING(x) __detail_AS_STRING(x)
#define __detail_AS_STRING(x) #x

#if DEBUG
#define DEBUG_PRINT(file, format, ...) fprintf(file, format, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) 0
#endif

#define RETURN_NULL_IF_NULL(ptr) RETURN_DEFAULT_IF_NULL(ptr, NULL)
#define RETURN_DEFAULT_IF_NULL(ptr, default) if ((ptr) == NULL) { \
  DEBUG_PRINT(stderr, "%s\n", "DEBUG: " #ptr " was NULL at " __FILE__ ":" AS_STRING(__LINE__)); \
  return (default);}
#define RETURN_VOID_IF_NULL(ptr) if ((ptr) == NULL) { \
  DEBUG_PRINT(stderr, "%s\n", "DEBUG: " #ptr " was NULL"); \
  return;}

#define FREE_RETURN_NULL(ptr, count, ...) if ((ptr) == NULL) { \
  free_many(count, __VA_ARGS__);    \
  RETURN_NULL_IF_NULL(ptr); \
}

void free_many(int count, ...);
