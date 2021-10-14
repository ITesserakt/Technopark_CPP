#include "Travel.h"

#include <string.h>

#include "utils.h"

Travel *new_travel(const char code[4], const char *departure_airport,
                   const char *arrival_airport, unsigned int flight_duration,
                   unsigned int cost) {
  RETURN_NULL_IF_NULL(code);
  RETURN_NULL_IF_NULL(departure_airport);
  RETURN_NULL_IF_NULL(arrival_airport);

  Travel *memory = malloc(sizeof(Travel));
  RETURN_NULL_IF_NULL(memory);

  memory->code = strdup(code);
  FREE_RETURN_NULL(memory->code, 1, &memory);
  memory->departure_airport = strdup(departure_airport);
  FREE_RETURN_NULL(memory->departure_airport, 2, &memory->code, &memory);
  memory->arrival_airport = strdup(arrival_airport);
  FREE_RETURN_NULL(memory->arrival_airport, 3, &memory->departure_airport,
                   &memory->code, &memory);
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

int compare_travels_by(const Travel *lhs, const Travel *rhs,
                       TravelProjection proj) {
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

static int get_cost(const Travel *t) { return t->cost; }

static int get_duration(const Travel *t) { return t->flight_duration; }

int compare_travels_by_cost(const Travel *lhs, const Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_cost);
}

int compare_travels_by_duration(const Travel *lhs, const Travel *rhs) {
  return compare_travels_by(lhs, rhs, get_duration);
}

const Travel *find_min_by(const Travel **travels, size_t length,
                          const char *from, const char *to,
                          TravelComparator comparator) {
  RETURN_NULL_IF_NULL(travels);
  RETURN_NULL_IF_NULL(from);
  RETURN_NULL_IF_NULL(to);
  RETURN_NULL_IF_NULL(comparator);
  if (length == 0)
    return NULL;

  const Travel *minimum = NULL;
  for (int i = 0; i < length; i++) {
    const Travel *travel = travels[i];
    if (strcmp(travel->departure_airport, from) == 0 &&
        strcmp(travel->arrival_airport, to) == 0 &&
        comparator(travel, minimum) < 0)
      minimum = travel;
  }
  return minimum;
}
