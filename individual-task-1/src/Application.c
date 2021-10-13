#include <string.h>
#include "Application.h"
#include "IO.h"
#include "utils.h"

#define BUFFER_SIZE 4
#define GROW_RATIO 2

static void prompt(FILE *output, const char *message) {
  RETURN_VOID_IF_NULL(output);
  RETURN_VOID_IF_NULL(message);

  if (output == stdout)
    fprintf(output, "%s", message);
}

static void show_error(FILE *output) {
  RETURN_VOID_IF_NULL(output);
  prompt(output, "Incorrect. Please repeat: ");
}

static void choose_load_method(FILE **in, FILE **out) {
  printf("Specify file to load travels table from: ");
  char *filename;
  while ((filename = read_line(stdin)) == NULL
      || (*in = fopen(filename, "r")) == NULL)
    show_error(stdout);
  free(filename);
  *out = *in;
}

Travel *load_travel(FILE *input, FILE *output) {
  RETURN_NULL_IF_NULL(input);
  RETURN_NULL_IF_NULL(output);
  prompt(output, "Enter travel code (e.g. SVO): ");
  char *code;
  if ((code = read_line(input)) == NULL || strlen(code) != 3) {
    if (!feof(input))
      printf("Incorrect travel code\n");
    FREE_RETURN_NULL(NULL, 1, &code);
  }

  prompt(output, "Enter departure airport: ");
  char *dep;
  if ((dep = read_line(input)) == NULL) {
    if (!feof(input))
      printf("Incorrect departure airport\n");
    FREE_RETURN_NULL(NULL, 2, &code, &dep);
  }

  prompt(output, "Enter arrival airport: ");
  char *arr;
  if ((arr = read_line(input)) == NULL) {
    if (!feof(input))
      printf("Incorrect arrival airport");
    FREE_RETURN_NULL(NULL, 3, &code, &dep, &arr);
  }

  prompt(output, "Enter flight duration in minutes: ");
  int64_t dur;
  if (read_long(input, &dur) != 0) {
    if (!feof(input))
      printf("Incorrect flight duration\n");
    FREE_RETURN_NULL(NULL, 3, &code, &dep, &arr);
  }

  prompt(output, "Enter flight cost: ");
  int64_t cost;
  if (read_long(input, &cost) != 0) {
    if (!feof(input))
      printf("Incorrect travel cost\n");
    FREE_RETURN_NULL(NULL, 3, &code, &dep, &arr);
  }

  Travel *result = new_travel(code, dep, arr, dur, cost);
  free_many(3, &code, &dep, &arr);
  return result;
}

const Travel **load_travels(FILE *input, FILE *output, size_t *length) {
  RETURN_NULL_IF_NULL(input);
  RETURN_NULL_IF_NULL(output);
  RETURN_NULL_IF_NULL(length);

  size_t travels_capacity = 2;
  const Travel **travels = malloc(travels_capacity * sizeof(Travel **));
  RETURN_NULL_IF_NULL(travels);

  const Travel *next;
  while ((next = load_travel(input, output)) != NULL) {
    if (travels_capacity == *length) {
      const Travel **grown = realloc(travels, travels_capacity *= GROW_RATIO);
      if (grown == NULL) {
        printf("Error while allocating memory, aborting...\n");
        FREE_RETURN_NULL(grown, 2, &travels, &next);
      }
      travels = grown;
    }
    travels[(*length)++] = next;
  }
  fflush(input);
  return travels;
}

const Travel *find_min_by(const Travel **travels,
                          size_t length,
                          char *from,
                          char *to,
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
    if (strcmp(travel->departure_airport, from) == 0
        && strcmp(travel->arrival_airport, to) == 0
        && comparator(minimum, travel) == -1)
      minimum = travel;
  }
  return minimum;
}

int run(int argc, char **argv) {
  FILE *in;
  FILE *out;

  choose_load_method(&in, &out);
  size_t travels_length = 0;
  const Travel **travels = load_travels(in, out, &travels_length);
  if (travels == NULL) {
    if (in != stdin)
      fclose(in);
    printf("Could not load travels properly\n");
    RETURN_DEFAULT_IF_NULL(travels, 1);
  }

  printf("Select from airport: ");
  char *from;
  while ((from = read_line(stdin)) == NULL)
    show_error(stdout);

  printf("Select to airport: ");
  char *to;
  while ((to = read_line(stdin)) == NULL)
    show_error(stdout);
  TravelComparator
      comparators[] = {compare_travels_by_duration, compare_travels_by_cost};

  printf("Find minimum travel by duration (0) or by cost (1): ");
  int64_t choice;
  while (read_long(stdin, &choice) != 0 || !(choice == 0 || choice == 1))
    show_error(stdout);

  const Travel *min =
      find_min_by(travels, travels_length, from, to, comparators[choice]);
  if (min == NULL)
    printf("Not found viable travel\n");
  else
    printf(
        "Travel { code: %s, departure airport: %s, arrival airport: %s, "
        "flight duration: %u, cost: %u }\n",
        min->code,
        min->departure_airport,
        min->arrival_airport,
        min->flight_duration,
        min->cost);

  for (int i = 0; i < travels_length; i++)
    destroy_travel((Travel *) travels[i]);
  free_many(3, &travels, &from, &to);
  if (in != stdin)
    fclose(in);

  return 0;
}
