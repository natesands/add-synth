#ifndef OSC_H
#define OSC_H

#include <boost/math/constants/constants.hpp>
#include <cmath>

const double pi = boost::math::constants::pi<double>();
enum {WAVE_SINE, WAVE_TRIANGLE, WAVE_SQUARE, WAVE_SAWUP, WAVE_SAWDOWN};
typedef double (*tickfunc)(double);

class Osc {
  public:
    Osc (unsigned long sample_rate, double freq, tickfunc f);
    double sample_rate;
    double freq;
    double phase;
    double incr;
    double twopiovrsr;
    tickfunc func;
    double tick();
};

double sinetick(double val) {
  return sin(val);
}

double Osc::tick() {
  double val = func(phase);
  phase += incr;
  if (phase >= 2*pi) 
    phase -= 2*pi;
  else if (phase < 0.0)
    phase += 2*pi;
  return val;
}


Osc::Osc(unsigned long sample_rate, double freq=1.0, tickfunc f=sin) {
  this->freq = freq;
  this->sample_rate = sample_rate;
  twopiovrsr = 2 * pi / (double) sample_rate;
  phase = 0.0;
  incr = freq * twopiovrsr;
  func  = f;
  }


#endif


