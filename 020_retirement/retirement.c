#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double cal_saving(double last_saving, double contribution, double rate_of_return) {
  return last_saving * (1 + rate_of_return) + contribution;
}

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired

  int age = startAge;
  double last_saving = initial;
  //working
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", age / 12, age % 12, last_saving);
    last_saving = cal_saving(last_saving, working.contribution, working.rate_of_return);
    age++;
  }
  //retired
  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2f\n", age / 12, age % 12, last_saving);
    last_saving = cal_saving(last_saving, retired.contribution, retired.rate_of_return);
    age++;
  }
}

int main() {
  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
