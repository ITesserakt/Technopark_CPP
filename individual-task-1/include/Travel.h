#pragma once

typedef struct Travel {
  char *code;
  char *departure_airport;
  char *arrival_airport;
  unsigned int flight_duration;
  unsigned int cost;
} Travel;

Travel *new_travel(const char code[4],
                   const char *departure_airport,
                   const char *arrival_airport,
                   unsigned int flight_duration,
                   unsigned int cost);

void destroy_travel(Travel *travel);

int compare_travels_by(Travel *lhs, Travel *rhs, int (*proj)(Travel*));

int compare_travels_by_cost(Travel* lhs, Travel* rhs);

int compare_travels_by_duration(Travel* lhs, Travel* rhs);