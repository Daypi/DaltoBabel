#pragma once

#include <iostream>
#include <string>
#include <list>
#include <portaudio.h>
#include "babel_common.h"
#include "IAudioIO.hh"

//#define SAMPLE_RATE  (44100)
//#define FRAMES_PER_BUFFER (512)
//#define NUM_SECONDS     (2)
//#define NUM_CHANNELS    (2)
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define	PLAYBACK	(1)

enum eBuffType
{
	RECORD,
	PLAY
};

typedef struct
{
  bool		available;
  int		frameIndex;
  int		maxFrameIndex;
  SAMPLE	*recordedSamples;
}	PortAudioBuffer;

class	PortAudioIO : public IAudioIO
{
private:
  PaStreamParameters		_inputParams;
  PaStreamParameters		_outputParams;
  PortAudioBuffer		_recordBuffers[2];
  PortAudioBuffer		_playBuffers[2];
  std::string			_errorString;
  short			        _recordingBuffer;
  short					_playingBuffer;
  int 					memberrecordCallback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
  static int 			recordCallback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
  int					_lastGetRecord;
public:
  PaStream			*_Stream;
  PaError			_err;
  PortAudioIO();
  bool					init(void);
  bool					cleanup(void);
  void					pushBuffer(PortAudioBuffer );
  bool					startRecording(void);
  const std::string		&getError();
  void					initRecording(void);
  float					*paLoop();
  void					switchBuffer(eBuffType);
  const float					*getRecord();
  void					setPlay(float *, int);
  virtual ~PortAudioIO();
};
