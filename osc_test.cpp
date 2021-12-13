#include <iostream>
#include "Osc.h"
using namespace std;

int main() {

  Osc osc {100,2};
  for (int i = 0; i < 200; i++)
   printf("%f ", osc.tick());
  printf("\n");
  return 0;
}


