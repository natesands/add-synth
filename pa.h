#ifndef PA_H
#define PA_H
#include "portaudio.h"
#include <iostream>

/* Portaudio interface functions */
const int buf_size = 256;

void error(PaError err) {
  Pa_Terminate();
  fprintf( stderr, "An error occured while using the portaudio stream\n" );
  fprintf( stderr, "Error number: %d\n", err );
  fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
  exit(1);
}

int osc_callback( const void *inputBuffer, void *outputBuffer, 
                           unsigned long framesPerBuffer, 
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
	Osc *osc = (Osc*)userData;
	float *out = (float*)outputBuffer;
	unsigned int i;
	(void) inputBuffer;  /* prevent unused variable warning */

	for(i=0; i< buf_size; i++ )
		*out++ = osc->tick();
	return 0;
}

/* Initialize portaudio */
void pa_init(int channels, PaStreamParameters &outputParameters) {
  PaError err; 
  //err = Pa_Initialize();
  outputParameters.device = Pa_GetDefaultOutputDevice();
  if (outputParameters.device == paNoDevice) {
    printf("Error: no default output device\n");
    exit(1);
  }

  outputParameters.channelCount = channels;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
}

void osc_play(Osc* osc, int dur) {
  PaStream *stream;
  PaError err;
  PaStreamParameters outputParameters;
  err = Pa_Initialize();
  
  /* Initialize portaudio and open stream */
  pa_init(1, outputParameters); 
  err = Pa_OpenStream( &stream,
                       NULL,     /* no input channels */
                       &outputParameters, 
                       osc->sample_rate,
                       buf_size,
                       paClipOff,
                       osc_callback,
                       osc);

  if (err != paNoError) error(err);
  
  /* Start stream */
  err = Pa_StartStream(stream);
  Pa_Sleep(dur*1000);

  /* Stop stream */
  err = Pa_StopStream(stream);
  if (err != paNoError) error(err);
  err = Pa_Terminate();
  if (err != paNoError)
    error(err);
}

#endif 
