#include "Travel.h"
#include "utils.h"
#include <string.h>

Travel *new_travel(const char code[4],
                   const char *departureAirport,
                   const char *arrivalAirport,
                   unsigned int flightDuration,
                   unsigned int cost) {
  RETURN_NULL_IF_NULL(departureAirport);
  RETURN_NULL_IF_NULL(arrivalAirport);

  Travel *memory = malloc(sizeof(Travel) + 1);
  RETURN_NULL_IF_NULL(memory);

  memory->code = strdup(code);
  FREE_RETURN_NULL(memory->code, 1, &memory);
  memory->departureAirport = strdup(departureAirport);
  FREE_RETURN_NULL(memory->departureAirport, 2, &memory->code, &memory);
  memory->arrivalAirport = strdup(arrivalAirport);
  FREE_RETURN_NULL(memory->arrivalAirport, 3, &memory->departureAirport, &memory->code, &memory);
  memory->flightDuration = flightDuration;
  memory->cost = cost;

  return memory;
}

void destroy_travel(Travel *travel) {
  RETURN_VOID_IF_NULL(travel);

  free(travel->code);
  free(travel->arrivalAirport);
  free(travel->departureAirport);

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
  return t->flightDuration;
}

int compare_travels_by_cost(Travel *lhs, Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_cost);
}

int compare_travels_by_duration(Travel *lhs, Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_duration);
}
