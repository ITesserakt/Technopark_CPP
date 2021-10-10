#pragma once

#include <stdlib.h>

#define RETURN_NULL_IF_NULL(ptr) if ((ptr) == NULL) return NULL
#define RETURN_DEFAULT_IF_NULL(ptr, default) if ((ptr) == NULL) return (default)
#define RETURN_VOID_IF_NULL(ptr) if ((ptr) == NULL) return