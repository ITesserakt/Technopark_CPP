#pragma once

#include <stdio.h>
#include "Travel.h"

void run(int argc, char** argv);

Travel *loadTravel(FILE* input, FILE* output);