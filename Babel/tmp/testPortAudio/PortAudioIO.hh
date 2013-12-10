#pragma once

#include <iostream>
#include <string>
#include <portaudio.h>
#include "IAudioIO.hh"

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (2)
#define NUM_CHANNELS    (2)
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)


#define	PLAYBACK	(1)

typedef struct
{
	bool		available;
    int          frameIndex;
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}	PortAudioBuffer;

class	PortAudioIO : public IAudioIO
{
private:
  PaStreamParameters	_inputParams;
  PaStreamParameters	_outputParams;
  PaStream				*_Stream;
  PaError				_err;
  PortAudioBuffer		_data[2];
  std::string			_errorString;
  short					_recordingBuffer;
  short					_playingBuffer;
  int 					memberrecordCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
  static int 			recordCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
  int 					memberplayCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
  static int 			playCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
public:
  PortAudioIO();
  bool					init(void);
  bool					cleanup(void);
  void					playSound(void);
  void					startRecording(void);
  const std::string		&getError();
  PortAudioBuffer		*getData();
  virtual ~PortAudioIO();
};
