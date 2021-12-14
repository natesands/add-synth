/* test program 
 * g++ --std=c++11 osc_test.cpp osc.cpp -lportaudio
 *
 */
#include <iostream>
#include "osc.h"
using namespace std;

int main() {
  OscBank bank{44100};
  Osc *osc1 = new Osc{44100, 200.0};
// osc1->phase += pi / 3.0;
  Osc *osc2 = new Osc{44100, 400.0};
  
  Osc *osc3 = new Osc{44100, 800.0};
  //Osc *osc2 = new Osc{44100, 300.0, square};
 // Osc *osc3 = new Osc{44100, 500.0};
  bank.add(osc2);
  bank.add(osc1);
  bank.add(osc3);
  bank.preview(3);
  //for (int i=0; i < 44100; i++)
  //    printf("%f\n", bank.tick());
  //bank.add(osc2);
 // bank.add(osc3);
//  osc2->preview(3);
//  bank.preview(3);
//  osc2->preview(3);
//  bank.preview(4);
//  Osc osc {44100,440};
//  osc.preview(3);
//  for (int i = 0; i < 200; i++)
//   printf("%f ", osc.tick());
//  printf("\n");
  return 0;
}


