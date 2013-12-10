#include	"PortAudioIO.hh"

PortAudioIO::PortAudioIO()
{
  
}

bool	PortAudioIO::init(void)
{
	this->_err = Pa_Initialize();
	this->_outputParams.device = Pa_GetDefaultOutputDevice();
	if (this->_outputParams.device == paNoDevice) {
		std::cerr << "Error: No default output device" << std::endl;
		return false;
	}
	this->_outputParams.channelCount = 2;                     /* stereo output */
	this->_outputParams.sampleFormat =  PA_SAMPLE_TYPE;
	this->_outputParams.suggestedLatency = Pa_GetDeviceInfo( this->_outputParams.device )->defaultLowOutputLatency;
	this->_outputParams.hostApiSpecificStreamInfo = NULL;
	if (this->_err != paNoError)
	{
	  std::cerr << this->getError() << std::endl;
	  return false;
	}
	return true;
}

bool	PortAudioIO::cleanup(void)
{
  this->_err =  Pa_Terminate();
  if (this->_err != paNoError)
  {
	  std::cerr << this->getError() << std::endl;
	  return false;
  }
  return true;
}


void	PortAudioIO::playSound(void)
{
	std::cout << "now playin back" << std::endl;
	this->_err = Pa_OpenStream(
	              &this->_Stream,
	              NULL,
	              &this->_outputParams,
	              SAMPLE_RATE,
	              FRAMES_PER_BUFFER,
	              paClipOff,
	              &PortAudioIO::playCallback,
	              this);
	  if (this->_err != paNoError)
	  {
		  std::cerr << this->getError() << std::endl;
		  return;
	  }
	if(this->_Stream)
	    {
	        this->_err = Pa_StartStream(this->_Stream);
	        while( ( this->_err = Pa_IsStreamActive( this->_Stream ) ) == 1 ) Pa_Sleep(100);
	        this->_err = Pa_CloseStream( this->_Stream );
	    }
}

int PortAudioIO::memberplayCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags)
{
//	SAMPLE *rptr = &this->_data[this->_playingBuffer].recordedSamples[this->_data[_playingBuffer].frameIndex * NUM_CHANNELS];
//	SAMPLE *wptr = (SAMPLE*)outputBuffer;
//	unsigned int i;
//	int finished;
//	unsigned int framesLeft = this->_data[this->_playingBuffer].maxFrameIndex - this->_data[this->_playingBuffer].frameIndex;
//
//	(void) inputBuffer;
//	(void) timeInfo;
//	(void) statusFlags;
//
//	if( framesLeft < framesPerBuffer )
//	{
//		/* final buffer... */
//		for( i=0; i<framesLeft; i++ )
//		{
//			*wptr++ = *rptr++;  /* left */
//			if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
//		}
//		for( ; i<framesPerBuffer; i++ )
//		{
//			*wptr++ = 0;  /* left */
//			if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
//		}
//		this->_data[this->_playingBuffer].frameIndex += framesLeft;
//		finished = paComplete;
//	}
//	else
//	{
//		for( i=0; i<framesPerBuffer; i++ )
//		{
//			*wptr++ = *rptr++;  /* left */
//			if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
//		}
//		this->_data[this->_playingBuffer].frameIndex += framesPerBuffer;
//		finished = paContinue;
//	}
//	return finished;
return 0;
}

int PortAudioIO::playCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
	return ((PortAudioIO*)userData)->memberplayCallback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}


void	PortAudioIO::startRecording(void)
{
	int			totalFrames;
	int			i;
	int			numSamples;
	int			numBytes;
	int			max, val;
	double		average;

	this->_recordingBuffer = 0;
	this->_playingBuffer = 1;
	this->_inputParams.device = Pa_GetDefaultInputDevice();
		if (this->_inputParams.device == paNoDevice) {
		   return;
		}
	this->_inputParams.channelCount = 2;
	this->_inputParams.sampleFormat = PA_SAMPLE_TYPE;
	this->_inputParams.suggestedLatency = Pa_GetDeviceInfo( this->_inputParams.device )->defaultLowInputLatency;
	this->_inputParams.hostApiSpecificStreamInfo = NULL;
	totalFrames = NUM_SECONDS * SAMPLE_RATE;
	numSamples = totalFrames * NUM_CHANNELS;
	for (int j = 0 ; j < 2 ; j++) { //init both buffers
		this->_data[j].recordedSamples = new float[numSamples];
		if( this->_data[j].recordedSamples == NULL )
		{
			return;
		}
	}
	while (42) {
		this->_data[_recordingBuffer].available = true;
		this->_data[_recordingBuffer].maxFrameIndex = totalFrames;
		this->_data[_recordingBuffer].frameIndex = 0;
		this->_data[_playingBuffer].frameIndex = 0;
		for( i=0; i< totalFrames; i++ ) {
			this->_data[_recordingBuffer].recordedSamples[i] = 0;
		}
		std::cout << "openstream" << std::endl;
		this->_err = Pa_OpenStream(
				  &this->_Stream,
				  &this->_inputParams,
				  &this->_outputParams,
				  SAMPLE_RATE,
				  FRAMES_PER_BUFFER,
				  paClipOff,
				  &PortAudioIO::recordCallback,
				  this);
		if (this->_err != paNoError)
				std::cerr << this->getError() << std::endl;
		this->_err = Pa_StartStream( this->_Stream );
		if (this->_err != paNoError)
				std::cerr << this->getError() << std::endl;

		while( ( this->_err = Pa_IsStreamActive(this->_Stream) ) == 1)
		{
			Pa_Sleep(1000);
			std::cout << "index: " << this->_data->frameIndex << std::endl;
		}
		this->_err = Pa_CloseStream(this->_Stream);
		if (this->_err != paNoError)
			std::cerr << this->getError() << std::endl;
		this->_playingBuffer = this->_recordingBuffer;
		this->_recordingBuffer = _recordingBuffer == 1 ? 0 : 1;
	}
}

int PortAudioIO::memberrecordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags)
{
	PortAudioBuffer	*data = &this->_data[this->_recordingBuffer];
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
	(void) timeInfo;
	(void) statusFlags;

	if(framesLeft < framesPerBuffer)
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}
	if( inputBuffer == NULL )
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = SAMPLE_SILENCE;  /* left */
			if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
		}
	}
	else
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if(NUM_CHANNELS == 2)
				*wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	if (PLAYBACK)
	{
		std::cout << "playingbuffer : " << _playingBuffer << std::endl;
		SAMPLE *rptr = &this->_data[this->_playingBuffer].recordedSamples[this->_data[_playingBuffer].frameIndex * NUM_CHANNELS];
		SAMPLE *wptr = (SAMPLE*)outputBuffer;
		unsigned int i2;
		int finished2;
		unsigned int framesLeft2 = this->_data[this->_playingBuffer].maxFrameIndex - this->_data[this->_playingBuffer].frameIndex;

		(void) inputBuffer;
		(void) timeInfo;
		(void) statusFlags;

		if( framesLeft2 < framesPerBuffer )
		{
			/* final buffer... */
			for( i2=0; i2<framesLeft2; i2++ )
			{
				*wptr++ = *rptr++;  /* left */
				if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
			}
			for( ; i2<framesPerBuffer; i2++ )
			{
				*wptr++ = 0;  /* left */
				if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
			}
			this->_data[this->_playingBuffer].frameIndex += framesLeft;
			finished2 = paComplete;
		}
		else
		{
			for( i2=0; i2<framesPerBuffer; i2++ )
			{
				*wptr++ = *rptr++;  /* left */
				if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
			}
			this->_data[this->_playingBuffer].frameIndex += framesPerBuffer;
			finished2 = paContinue;
		}
	}
	return finished;
}

int PortAudioIO::recordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
	return ((PortAudioIO*)userData)->memberrecordCallback(inputBuffer, outputBuffer,
			framesPerBuffer, timeInfo, statusFlags);
}

PortAudioBuffer			*PortAudioIO::getData()
{
	return &this->_data[0];
}

const std::string	&PortAudioIO::getError()
{
  this->_errorString = Pa_GetErrorText(this->_err);
  return this->_errorString;
}

PortAudioIO::~PortAudioIO()
{

}
