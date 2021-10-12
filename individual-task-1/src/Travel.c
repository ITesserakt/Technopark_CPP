#include "Travel.h"
#include "utils.h"
#include <string.h>

Travel *new_travel(const char code[4],
                   const char *departure_airport,
                   const char *arrival_airport,
                   unsigned int flight_duration,
                   unsigned int cost) {
  RETURN_NULL_IF_NULL(departure_airport);
  RETURN_NULL_IF_NULL(arrival_airport);

  Travel *memory = malloc(sizeof(Travel) + 1);
  RETURN_NULL_IF_NULL(memory);

  memory->code = strdup(code);
  FREE_RETURN_NULL(memory->code, 1, &memory);
  memory->departure_airport = strdup(departure_airport);
  FREE_RETURN_NULL(memory->departure_airport, 2, &memory->code, &memory);
  memory->arrival_airport = strdup(arrival_airport);
  FREE_RETURN_NULL(memory->arrival_airport, 3, &memory->departure_airport, &memory->code, &memory);
  memory->flight_duration = flight_duration;
  memory->cost = cost;

  return memory;
}

void destroy_travel(Travel *travel) {
  RETURN_VOID_IF_NULL(travel);

  free(travel->code);
  free(travel->arrival_airport);
  free(travel->departure_airport);

  free(travel);
}

int compare_travels_by(Travel *lhs, Travel *rhs, int (*proj)(Travel *)) {
  RETURN_DEFAULT_IF_NULL(lhs, -2);
  RETURN_DEFAULT_IF_NULL(rhs, -3);
  RETURN_DEFAULT_IF_NULL(proj, -4);

  int left = proj(lhs);
  int right = proj(rhs);

  if (left > right)
    return 1;
  else if (left == right)
    return 0;
  return -1;
}

static int get_cost(Travel* t) {
  return t->cost;
}

static int get_duration(Travel* t) {
  return t->flight_duration;
}

int compare_travels_by_cost(Travel *lhs, Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_cost);
}

int compare_travels_by_duration(Travel *lhs, Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_duration);
}
