#pragma once

#include <string>
#include "portaudio.h"
#include "babel_common.h"

typedef struct
{
    int			frameIndex;  /* Index into sample array. */
    int			maxFrameIndex;
    float		*sampleBuffer;
} t_sampleData;

class PaWin
{
	PaStreamParameters  _inputParameters;
	PaStreamParameters	_outputParameters;
	PaStream*			_stream;
	PaError				_err;
	t_sampleData		_data;

public:
	PaWin(void);
	~PaWin(void);

	void	CreateStream(); // record
	void	openStream(); // listen
	void	closeStream(); // end

	void	record();
	void	play();
};

/* ____________________ PortAudio Callbacks ____________________ */

static int recordCallback( const void *inputBuffer, void *outputBuffer,
						  unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
						  PaStreamCallbackFlags statusFlags, void *userData );
static int playCallback( const void *inputBuffer, void *outputBuffer,
						unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags, void *userData );