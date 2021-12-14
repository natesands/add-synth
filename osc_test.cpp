/* test program 
 * g++ --std=c++11 osc_test.cpp osc.cpp -lportaudio
 *
 */
#include <iostream>
#include "osc.h"
using namespace std;

int main() {

  Osc osc {44100,440};
  osc.preview(3);
  for (int i = 0; i < 200; i++)
   printf("%f ", osc.tick());
  printf("\n");
  return 0;
}


