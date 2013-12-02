#pragma once

#include <iostream>
#include <string>
#include <portaudio.h>

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
#define WRITE_TO_FILE   (0)

//particulierement hideux !

#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int          frameIndex;
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}paTestData;

class	PortAudioManager
{
private:
  PaStreamParameters	_inputParams;
  PaStreamParameters	_outputParams;
  PaStream				*_Stream;
  PaError				_err;
  paTestData			_data;
  std::string			_errorString;

  int 					memberrecordCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
  static int 			recordCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
  int 					memberplayCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
  static int 			playCallback( const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
public:
  PortAudioManager();
  bool			init(void);
  bool			cleanup(void);
  void			playSound(void);
  void			recordSound(void);
  const std::string	&getError();
  ~PortAudioManager();
};
