#ifndef OSC_H
#define OSC_H

#include <boost/math/constants/constants.hpp>

/*--------------------------------------------------------------------------------
Oscillator class and associated wave functions.
--------------------------------------------------------------------------------*/

const double pi = boost::math::constants::pi<double>();

typedef double (*tickfunc)(double);

class Osc {
  public:
    Osc (unsigned long sample_rate, double freq, tickfunc f);
    double sample_rate;
    double freq;
    double phase;
    double incr;                // SR * incr = freq * 2pi
    double twopiovrsr;          // 2 pi / sample_rate
    tickfunc func;              // pointer to oscillator func
    double tick();              // returns next frame and advances phase
};

/*  Waveform functions */
double square(double phase);
double sawup(double phase);
double sawdown(double phase);
double triangle(double phase);


#endif


