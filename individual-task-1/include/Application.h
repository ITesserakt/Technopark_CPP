#pragma once

#include <stdio.h>
#include "Travel.h"

int run(int argc, char **argv);

Travel *load_travel(FILE *input, FILE *output);

const Travel **load_travels(FILE *input, FILE *output, size_t *length);

const Travel *find_min_by(const Travel **travels,
                          size_t length,
                          char *from,
                          char *to,
                          TravelComparator comparator);
