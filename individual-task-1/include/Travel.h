#pragma once

typedef struct Travel {
  char *code;
  char *departureAirport;
  char *arrivalAirport;
  unsigned int flightDuration;
  unsigned int cost;
} Travel;

Travel *new_travel(const char code[4],
                   const char *departureAirport,
                   const char *arrivalAirport,
                   unsigned int flightDuration,
                   unsigned int cost);

void destroy_travel(Travel *travel);

int compare_travels_by(Travel *lhs, Travel *rhs, int (*proj)(Travel*));
