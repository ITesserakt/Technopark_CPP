#pragma once

#include <stdio.h>

#include "Travel.h"

int run(int argc, const char **argv);

Travel *load_travel(FILE *input, FILE *output);

const Travel **load_travels(FILE *input, FILE *output, size_t *length);
