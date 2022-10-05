#include "pandemic.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

//takes a line ina csv file and extract country name and population
//in the format country name,population
country_t parseLine(char * line) {
  country_t ans;
  int index = 0;
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

  /* get country name */
  while (line[index] != ',') {
    ans.name[index] = line[index];
    index++;
  }
  ans.name[index] = '\0';

  index++;  //index now at the first chatacter after ','

  //length of char population: population digits number
  size_t pop_len = 0;

  /* get population */
  while (line[index] != '\n') {
    //valid with space
    if (line[index] == ' ' && pop_len == 0) {
      index++;
      continue;
    }
    //overflow: population length larger than 20
    if (pop_len == 20) {
      perror("Overflow: Population too large");
      exit(EXIT_FAILURE);
    }

    //invalid input with characters cannot convert to digits
    if (!isdigit(line[index])) {
      perror("Invalid Population: contain invalid character");
      exit(EXIT_FAILURE);
    }

    population[pop_len] = line[index];
    pop_len++;
    index++;
  }
  population[pop_len] = '\0';

  //check empty population
  if (pop_len == 0) {
    perror("Invalid line: No population data");
    exit(EXIT_FAILURE);
  }

  //check overflow: 20 digits.
  if (pop_len == 20) {
    uint64_t max_num = UINT64_MAX;
    char max_char[21];
    // printf("%s and %lu\n", population, max_num);
    sprintf(max_char, "%lu", max_num);
    for (int i = 0; i < 21; i++) {
      if (population[i] < max_char[i]) {
        break;
      }
      else if (population[i] == max_char[i]) {
        continue;
      }
      else {
        perror("Overflow: Population too large\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  ans.population = strtoull(population, NULL, 10);

  return ans;
}

/* calculate 7 days running average of case data
data: daily case data; avg: result of calculation
 */
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //do nothing and EXIT success when n_days < 6
  if (n_days < 7) {
    exit(EXIT_SUCCESS);
  }

  double sum = 0.0;
  for (size_t i = 0; i < n_days - 6; i++) {
    sum = 0;
    for (size_t j = 0; j < 7; j++) {
      sum += data[i + j];
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
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
  unsigned max_data;
  size_t max_country;
  for (size_t day = 0; day < n_days; day++) {
    max_data = 0;
    max_country = 0;
    for (size_t ctr_i = 0; ctr_i < n_countries; ctr_i++) {
      if (data[ctr_i][day] > max_data) {
        max_data = data[ctr_i][day];
        max_country = ctr_i;
      }
    }
    printf(
        "%s has the most daily cases with %u\n", countries[max_country].name, max_data);
  }
}
