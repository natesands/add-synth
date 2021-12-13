#include "Osc.h"
#include <cmath>

/* Constructor : registers oscillator's generating function */
Osc::Osc(unsigned long sample_rate, double freq=1.0, tickfunc f=sin) {
  this->freq = freq;
  this->sample_rate = sample_rate;
  twopiovrsr = 2 * pi / (double) sample_rate;
  phase = 0.0;
  incr = freq * twopiovrsr;
  func  = f;
}

/* Return's next frame and advances phase by freq * 2pi / sample_rate */
double Osc::tick() {
  double val = func(phase);
  phase += incr;
  if (phase >= 2*pi) 
    phase -= 2*pi;
  else if (phase < 0.0)
    phase += 2*pi;
  return val;
}

/* Waveforms */
double square(double phase) {
  double val;
  val = sine(phase) < 0 ? -1.0 : 1.0;
  return val;
}

double sawup(double phase) {
  double val;
  val = phase / pi - 1;
  return val;
}

double sawdown(double phase) {
  double val;
  val = -phase / pi + 1;
  return val;
}

double triangle(double phase) {
  double val;
  val = phase < pi ? phase * 2.0 / pi - 1 : 3 - phase * 2.0 / pi;
  return val;
}


