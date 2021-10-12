#include <string.h>
#include "Application.h"
#include "IO.h"
#include "utils.h"

static void prompt(FILE *output, const char *message) {
  if (output == NULL || message == NULL)
    return;
  if (output == stdout)
    fprintf(output, "%s", message);
}

static void show_error(FILE *output) {
  if (output == NULL)
    return;
  if (output == stdout)
    prompt(output, "Incorrect. Please repeat: ");
}

Travel *loadTravel(FILE *input, FILE *output) {
  RETURN_NULL_IF_NULL(input);
  RETURN_NULL_IF_NULL(output);
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

void run(int argc, char **argv) {
  printf("Hello! Please choose a method to load travels table:\n"
         "    1 - from console, 2 - from file\n");
  long choice;
  while (read_long(stdin, &choice) != 0 || !(choice == 1 || choice == 2))
    show_error(stdout);

  FILE *file;
  FILE *out;
  if (choice == 1) {
    printf("Ok, let's load your travels...\n");
    file = stdin;
    out = stdout;
  } else {
    printf("Specify file to load from: ");
    char *filename;
    while ((filename = read_line(stdin)) == NULL || (file = fopen(filename, "r")) == NULL)
      show_error(stdout);
    out = file;
  }

  loadTravel(file, out);
  if (file != stdin) {
    fclose(file);
    fclose(out);
  }
}
