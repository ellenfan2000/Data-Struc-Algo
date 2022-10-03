#include "pandemic.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  int index = 0;
  // char * population = line;
  char population[21];

  //check comma exist
  if (strchr(line, ',') == NULL) {
    perror("Not valid line\n");
    exit(EXIT_FAILURE);
  }
  //check the line only has one comma
  if (strrchr(line, ',') != strchr(line, ',')) {
    perror("Invalid line\n");
    exit(EXIT_FAILURE);
  }

  //get country name
  while (line[index] != ',') {
    ans.name[index] = line[index];
    index++;
  }
  ans.name[index] = '\0';

  //get population
  //line += index + 1;
  //strcpy(population, line);
  //population += index + 1;

  index++;  //index now at the first chatacter after ','

  size_t pop_len = 0;
  while (line[index] != '\n') {
    //valid with space
    if (line[index] == ' ') {
      index++;
      continue;
    }
    //overflow: population length larger than 20
    if (pop_len == 20) {
      perror("Overflow: Population too large");
      exit(EXIT_FAILURE);
    }

    //invalid input:cannot convert to digits
    if (!isdigit(line[index])) {
      perror("Invalid Population: contain invalid character");
      exit(EXIT_FAILURE);
    }
    population[pop_len] = line[index];
    pop_len++;
    index++;
  }
  population[pop_len] = '\0';

  //check no population data
  /* if (*population == '\n') { */
  /*   perror("Invalid Line: no popualtion data"); */
  /*   exit(EXIT_FAILURE); */
  /* } */
  if (pop_len == 0) {
    perror("Invalid line: No population data");
    exit(EXIT_FAILURE);
  }
  //check overflow

  ans.population = atoll(population);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {
    perror("not enough data");
    exit(EXIT_FAILURE);
  }

  double sum = 0;

  for (size_t i = 0; i < n_days - 6; i++) {
    for (size_t j = 0; j < 7; j++) {
      sum += data[i + j];
      /* if(){ */
      /* 	perror("overflow!"); */
      /* 	exit(EXIT_FAILURE); */
      /* } */
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  unsigned cum_sum = 0;
  if (pop == 0) {
    perror("population is 0");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days; i++) {
    cum_sum += data[i];
    cum[i] = cum_sum * (double)100000 / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned max;
  size_t max_country;
  for (size_t day = 0; day < n_days; day++) {
    max = 0;
    max_country = 0;
    for (size_t ctr_i = 0; ctr_i < n_countries; ctr_i++) {
      if (data[ctr_i][day] > max) {
        max = data[ctr_i][day];
        max_country = ctr_i;
      }
    }
    printf("%s has the most daily cases with %u\n", countries[max_country].name, max);
  }
}
