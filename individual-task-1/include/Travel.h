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

typedef int (*TravelComparator)(const Travel*, const Travel*);
typedef int (*TravelProjection)(const Travel*);

int compare_travels_by(const Travel *lhs, const Travel *rhs, TravelProjection proj);

int compare_travels_by_cost(const Travel* lhs, const Travel* rhs);

int compare_travels_by_duration(const Travel* lhs, const Travel* rhs);
