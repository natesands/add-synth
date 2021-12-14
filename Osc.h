#ifndef OSC_H
#define OSC_H

#include <boost/math/constants/constants.hpp>

/*--------------------------------------------------------------------------------
  Oscillator class and associated wave functions.
--------------------------------------------------------------------------------*/

const float pi = boost::math::constants::pi<float>();

typedef float (*tickfunc)(float);

class Osc {
  public:
    Osc (unsigned long sample_rate, float freq=1.0, tickfunc f=sin);
    float sample_rate;
    float tick();              /* Returns next frame and advances phase */
    void preview(int dur);      /* Plays sound for given duration */
    float freq;
    float phase;
    float incr;                /* incr = freq * 2pi / sample_rate */
    float twopiovrsr;          /* 2 pi / sample_rate */
    tickfunc func;              /* Pointer to oscillator's generating function */
};

/*  Waveform functions */
float square(float phase);
float sawup(float phase);
float sawdown(float phase);
float triangle(float phase);


#endif


