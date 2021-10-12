#include <string.h>
#include "Application.h"
#include "IO.h"
#include "utils.h"

void run(int argc, char **argv) {
  Travel *t = loadTravel(stdin, stdout);

  printf("%s, %s, %s, %u, %u", t->code, t->departureAirport, t->arrivalAirport, t->flightDuration, t->cost);
}

static void prompt(FILE *output, const char *message) {
  if (output == stdout)
    fprintf(output, "%s", message);
}

static void show_error(FILE *output) {
  if (output == stdout)
    prompt(output, "Incorrect. Please repeat: ");
}

Travel *loadTravel(FILE *input, FILE *output) {
  prompt(output, "Enter travel code (e.g. SVO): ");
  char *code;
  while ((code = read_line(input)) == NULL || strlen(code) != 3)
    show_error(output);

  prompt(output, "Enter departure airport: ");
  char *dep;
  while ((dep = read_line(input)) == NULL)
    show_error(output);

  prompt(output, "Enter arrival airport: ");
  char *arr;
  while ((arr = read_line(input)) == NULL)
    show_error(output);

  prompt(output, "Enter flight duration in minutes: ");
  long dur;
  while (read_long(input, &dur) != 0)
    show_error(output);

  prompt(output, "Enter flight cost: ");
  long cost;
  while (read_long(input, &cost) != 0)
    show_error(output);

  Travel *result = new_travel(code, dep, arr, dur, cost);
  free_many(3, &code, &dep, &arr);
  return result;
}