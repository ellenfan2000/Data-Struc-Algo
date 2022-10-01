#include "pandemic.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  int index = 0;
  char population[21];
  if (strchr(line, ',') == NULL) {
    perror("Not valid line\n");
    exit(EXIT_FAILURE);
  }
  if (strrchr(line, ',') != strchr(line, ',')) {
    perror("Invalid line\n");
    exit(EXIT_FAILURE);
  }

  while (line[index] != ',') {
    ans.name[index] = line[index];
    index++;
  }
  index++;
  ans.name[index] = '\0';
  line += index;
  strcpy(population, line);

  ans.population = atoll(population);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
