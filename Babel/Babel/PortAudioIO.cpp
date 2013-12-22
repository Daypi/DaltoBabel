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

void	PortAudioIO::pushBuffer(PortAudioBuffer buf)
{
    std::cout << "maxframeindex:" << buf.maxFrameIndex << std::endl;
  int	idBuffer = _playingBuffer == 1 ? 0 : 1;
  buf.frameIndex = 0;
  std::cout << "pushing in " << idBuffer << std::endl;
  this->_playBuffers[idBuffer] = buf;
}

bool	PortAudioIO::startRecording(void)
{
	int totalFrames = NUM_SECONDS * SAMPLE_RATE;
	int numSamples = totalFrames * NUM_CHANNELS;
	int			i;
	int			numBytes;
	int			max, val;
	double		average;

  this->_recordingBuffer = 0;
  this->_playingBuffer = 0;
  this->_inputParams.device = Pa_GetDefaultInputDevice();
  if (this->_inputParams.device == paNoDevice)
    return false;
  this->_inputParams.channelCount = 2;
  this->_inputParams.sampleFormat = PA_SAMPLE_TYPE;
  this->_inputParams.suggestedLatency = Pa_GetDeviceInfo( this->_inputParams.device )->defaultLowInputLatency;
  this->_inputParams.hostApiSpecificStreamInfo = NULL;
  
  for (int j = 0 ; j < 2 ; j++)
  {
    this->_recordBuffers[j].recordedSamples = new float[numSamples];
    if( this->_recordBuffers[j].recordedSamples == NULL )
		return false;
    this->_playBuffers[j].recordedSamples = new float[numSamples];
    if( this->_playBuffers[j].recordedSamples == NULL )
		return false;
  }
/*  while (42) {
    std::cout << std::endl << std::endl;
    std::cout << "playing in " << _playingBuffer << std::endl;
    std::cout << "recording in" << _recordingBuffer << std::endl;
    this->_recordBuffers[_recordingBuffer].maxFrameIndex = totalFrames;
    this->_recordBuffers[_recordingBuffer].frameIndex = 0;
    this->_playBuffers[_playingBuffer].frameIndex = 0;
    for( i=0; i< totalFrames; i++ ) {
      this->_recordBuffers[_recordingBuffer].recordedSamples[i] = 0;
    }
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
	Pa_Sleep(100);
      }
    this->_err = Pa_CloseStream(this->_Stream);
    if (this->_err != paNoError)
      std::cerr << this->getError() << std::endl;
    std::cout << "maxframeindex:" << this->_recordBuffers[_recordingBuffer].maxFrameIndex << std::endl;
    this->pushBuffer(this->_recordBuffers[_recordingBuffer]);
    _recordingBuffer = _recordingBuffer == 1 ? 0 : 1;
    for( i=0; i< totalFrames; i++ ) {
       this->_playBuffers[_playingBuffer].recordedSamples[i] = 0;
    }
    _playingBuffer = _playingBuffer == 1 ? 0 : 1;
  }*/
  return true;
}

float *PortAudioIO::paLoop(float *in)
{
	int i;
	int totalFrames = NUM_SECONDS * SAMPLE_RATE;
	int numSamples = totalFrames * NUM_CHANNELS;
    std::cout << std::endl << std::endl;
    std::cout << "playing in " << _playingBuffer << std::endl;
    std::cout << "recording in" << _recordingBuffer << std::endl;
    this->_recordBuffers[_recordingBuffer].maxFrameIndex = totalFrames;
    this->_recordBuffers[_recordingBuffer].frameIndex = 0;
    this->_playBuffers[_playingBuffer].frameIndex = 0;
    for( i=0; i< totalFrames; i++ ) {
      this->_recordBuffers[_recordingBuffer].recordedSamples[i] = 0;
    }
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
	//	Pa_Sleep(1);
      }
    this->_err = Pa_CloseStream(this->_Stream);
    if (this->_err != paNoError)
      std::cerr << this->getError() << std::endl;
    std::cout << "maxframeindex:" << this->_recordBuffers[this->_recordingBuffer].maxFrameIndex << std::endl;
    this->pushBuffer(this->_recordBuffers[this->_recordingBuffer]);
    this->_recordingBuffer = this->_recordingBuffer == 1 ? 0 : 1;
    for( i=0; i< totalFrames; i++ ) {
       this->_playBuffers[this->_playingBuffer].recordedSamples[i] = 0;
    }
    this->_playingBuffer = this->_playingBuffer == 1 ? 0 : 1;
	return (this->_recordingBuffer == 1 ? this->_recordBuffers[0].recordedSamples : this->_recordBuffers[1].recordedSamples);
}

int PortAudioIO::memberrecordCallback( const void *inputBuffer, void *outputBuffer,
				       unsigned long framesPerBuffer,
				       const PaStreamCallbackTimeInfo* timeInfo,
				       PaStreamCallbackFlags statusFlags)
{
	PortAudioBuffer	*data = &this->_recordBuffers[this->_recordingBuffer];
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

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
		SAMPLE *rptr = &_playBuffers[_playingBuffer].recordedSamples[_playBuffers[_playingBuffer].frameIndex * NUM_CHANNELS];
		SAMPLE *wptr = (SAMPLE*)outputBuffer;
		unsigned int i2;
		int finished2;
		unsigned int framesLeft2 = _playBuffers[_playingBuffer].maxFrameIndex - _playBuffers[_playingBuffer].frameIndex;

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
			this->_playBuffers[this->_playingBuffer].frameIndex += framesLeft;
			finished2 = paComplete;
		}
		else
		{
			for( i2=0; i2<framesPerBuffer; i2++ )
			{
				*wptr++ = *rptr++;  /* left */
				if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
			}
			this->_playBuffers[this->_playingBuffer].frameIndex += framesPerBuffer;
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
  return &this->_recordBuffers[0];
}

const std::string	&PortAudioIO::getError()
{
  this->_errorString = Pa_GetErrorText(this->_err);
  return this->_errorString;
}

PortAudioIO::~PortAudioIO()
{

}
