#include "osc.h"
#include "pa.h"
#include <cmath>

/* Constructor : registers oscillator's generating function.  
 * Defaults to freq=1.0 and f=sin. 
 */
Osc::Osc(unsigned long sample_rate, float freq, tickfunc f) {
  this->freq = freq;
  this->sample_rate = sample_rate;
  twopiovrsr = 2 * pi / (float) sample_rate;
  phase = 0.0;
  incr = freq * twopiovrsr;
  func  = f;
}

/* Return's next frame and advances phase by freq * 2pi / sample_rate */
float Osc::tick() {
  float val = func(phase);
  //printf("%f\n",val);
  phase += incr;
  if (phase >= 2*pi) 
    phase -= 2*pi;
  else if (phase < 0.0)
    phase += 2*pi;
  return val;
}

/* Play sound for given number of seconds */
void Osc::preview(int dur) {
  osc_play(this, dur);
  phase = 0.0;  /* reset phase */
}

void OscBank::add(Osc *osc_ptr) {
  if (osc_ptr->sample_rate != sample_rate) {
    printf("Sample rate does not match...\n Oscilator not added to bank.\n");
    return;
  }
  osc_bank.push_back(osc_ptr);
}

float OscBank::tick() {
  if (osc_bank.size() == 0) return 0.0;
  float val;
  for (int i=0; i < osc_bank.size(); i++) {
  //  printf("%d\n",i);
    val += osc_bank[i]->tick();
  }
 // printf("%f\n",val);
  return val;
//  for (auto osc_ptr : osc_bank)
//    val += osc_ptr->tick();

//  return val;
}

void OscBank::preview(int dur) {
  oscbank_play(this, dur);
  for (int i=0; i< osc_bank.size(); i++)
    osc_bank[i]->phase = 0.0;
}

/* Waveforms */
float square(float phase) {
  float val;
  val = sin(phase) < 0 ? -1.0 : 1.0;
  return val;
}

float sawup(float phase) {
  float val;
  val = phase / pi - 1;
  return val;
}

float sawdown(float phase) {
  float val;
  val = -phase / pi + 1;
  return val;
}

float triangle(float phase) {
  float val;
  val = phase < pi ? phase * 2.0 / pi - 1 : 3 - phase * 2.0 / pi;
  return val;
}


