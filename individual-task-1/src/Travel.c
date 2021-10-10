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
  RETURN_NULL_IF_NULL(memory->code);
  memmove(memory->departureAirport, departureAirport, strlen(departureAirport) + 1);
  memmove(memory->arrivalAirport, arrivalAirport, strlen(arrivalAirport) + 1);
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
  if (proj(lhs) > proj(rhs))
    return 1;
  else if (proj(lhs) == proj(rhs))
    return 0;
  return -1;
}
