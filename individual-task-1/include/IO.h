#pragma once

#include <stdio.h>

char* read_line(FILE* input);

char* read_word(FILE* input);

#define READ_ERROR 1
#define PARSE_ERROR 2

int read_long(FILE* input, long *out);
