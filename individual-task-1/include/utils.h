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
  DEBUG_PRINT(stderr, "DEBUG: %s was NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
  return (default);} 0
#define RETURN_VOID_IF_NULL(ptr) if ((ptr) == NULL) { \
  DEBUG_PRINT(stderr, "DEBUG: %s was NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
  return;} 0

#define FREE_RETURN_NULL(ptr, count, ...) FREE_RETURN_DEFAULT(ptr, NULL, count, __VA_ARGS__)

#define FREE_RETURN_DEFAULT(ptr, default, count, ...) if ((ptr) == NULL) { \
  free_many(count, __VA_ARGS__);    \
  RETURN_DEFAULT_IF_NULL(ptr, default); \
} 0

void free_many(int count, ...);
