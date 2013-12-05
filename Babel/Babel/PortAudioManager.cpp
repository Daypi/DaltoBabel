#include	"PortAudioManager.hh"

PortAudioManager::PortAudioManager()
{
  
}

bool	PortAudioManager::init(void)
{
  this->_err = Pa_Initialize();
  if (this->_err != paNoError)
  {
	  std::cerr << this->getError() << std::endl;
	  return false;
  }
  return true;
}

bool	PortAudioManager::cleanup(void)
{
  this->_err =  Pa_Terminate();
  if (this->_err != paNoError)
  {
	  std::cerr << this->getError() << std::endl;
	  return false;
  }
  return true;
}


void	PortAudioManager::playSound(void)
{
	this->_data.frameIndex = 0;
	this->_outputParams.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (this->_outputParams.device == paNoDevice) {
		std::cerr << "Error: No default output device" << std::endl;
		return;
	}
	this->_outputParams.channelCount = 2;                     /* stereo output */
	this->_outputParams.sampleFormat =  PA_SAMPLE_TYPE;
	this->_outputParams.suggestedLatency = Pa_GetDeviceInfo( this->_outputParams.device )->defaultLowOutputLatency;
	this->_outputParams.hostApiSpecificStreamInfo = NULL;
	std::cout << "now playin back" << std::endl;
	this->_err = Pa_OpenStream(
	              &this->_Stream,
	              NULL, /* no input */
	              &this->_outputParams,
	              SAMPLE_RATE,
	              FRAMES_PER_BUFFER,
	              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
	              &PortAudioManager::playCallback,
	              this);
	  if (this->_err != paNoError)
	  {
		  std::cerr << this->getError() << std::endl;
		  return;
	  }
	if(this->_Stream)
	    {
	        this->_err = Pa_StartStream(this->_Stream);
	        std::cout << "Waiting for playback to finish" << std::endl;

	        while( ( this->_err = Pa_IsStreamActive( this->_Stream ) ) == 1 ) Pa_Sleep(100);
	        this->_err = Pa_CloseStream( this->_Stream );
	        std::cout << "done" << std::endl;
	    }
}

int PortAudioManager::memberplayCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags)
{
	SAMPLE *rptr = &this->_data.recordedSamples[this->_data.frameIndex * NUM_CHANNELS];
	SAMPLE *wptr = (SAMPLE*)outputBuffer;
	unsigned int i;
	int finished;
	unsigned int framesLeft = this->_data.maxFrameIndex - this->_data.frameIndex;

	(void) inputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;

	if( framesLeft < framesPerBuffer )
	{
		/* final buffer... */
		for( i=0; i<framesLeft; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
		}
		for( ; i<framesPerBuffer; i++ )
		{
			*wptr++ = 0;  /* left */
			if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
		}
		this->_data.frameIndex += framesLeft;
		finished = paComplete;
	}
	else
	{
		for( i=0; i<framesPerBuffer; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
		}
		this->_data.frameIndex += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}

int PortAudioManager::playCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
	return ((PortAudioManager*)userData)->memberplayCallback(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}


void	PortAudioManager::recordSound(void)
{
	int			totalFrames;
	int			i;
	int			numSamples;
	int			numBytes;
	int			max, val;
	double		average;

	std::cout << NUM_SECONDS << " " << SAMPLE_RATE << std::endl;
	this->_data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
	this->_data.frameIndex = 0;
	numSamples = totalFrames * NUM_CHANNELS;
	this->_data.recordedSamples = new float[numSamples]; /* From now on, recordedSamples is initialised. */
	if( this->_data.recordedSamples == NULL )
	{
		std::cout << "Could not allocate record array" << std::endl;
		return;
	}
	for( i=0; i<numSamples; i++ )
	{
		this->_data.recordedSamples[i] = 0;
	}
	this->_inputParams.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (this->_inputParams.device == paNoDevice) {
	   std::cerr << "Error: No default input device" << std::endl;
	   return;
	}
	this->_inputParams.channelCount = 2;                    /* stereo input */
	this->_inputParams.sampleFormat = PA_SAMPLE_TYPE;
	this->_inputParams.suggestedLatency = Pa_GetDeviceInfo( this->_inputParams.device )->defaultLowInputLatency;
	this->_inputParams.hostApiSpecificStreamInfo = NULL;


    this->_err = Pa_OpenStream(
              &this->_Stream,
              &this->_inputParams,
              NULL,               /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              &PortAudioManager::recordCallback,
              this);
    if (this->_err != paNoError)
        	std::cerr << this->getError() << std::endl;
    this->_err = Pa_StartStream( this->_Stream );
    if (this->_err != paNoError)
        	std::cerr << this->getError() << std::endl;
    std::cout << "\n=== Now recording!! Please speak into the microphone. ===\n" << std::endl;
    while( ( this->_err = Pa_IsStreamActive(this->_Stream) ) == 1)
    {
        Pa_Sleep(1000);
    	std::cout << "index: " << this->_data.frameIndex << std::endl;
    }
    this->_err = Pa_CloseStream(this->_Stream);
    if (this->_err != paNoError)
    	std::cerr << this->getError() << std::endl;
    max = 0;
    average = 0.0;
	for( i=0; i<numSamples; i++ )
	{
		val = this->_data.recordedSamples[i];
		//std::cout << "val:" << val << std::endl;
		if( val < 0 ) val = -val; /* ABS */
		if( val > max )
		{
			//std::cout << "max:" << max << std::endl;
		}
		average += val;
	}

	average = average / (double)numSamples;

	std::cout << "sample max amplitude = " <<  max << std::endl;
	std::cout << "sample average = " <<  average << std::endl;
}

int PortAudioManager::memberrecordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags, void *userData)
{
	paTestData	*data = (paTestData*)userData;
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = this->_data.maxFrameIndex - this->_data.frameIndex;
	(void) outputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;

	if( framesLeft < framesPerBuffer )
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}
	//std::cout  << framesToCalc << " framestocalc" <<  std::endl;

	if( inputBuffer == NULL )
	{

		//for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = SAMPLE_SILENCE;  /* left */
			if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
		}
	}
	else
	{
		//std::cout << "inputbuffer NOT null" << std::endl;
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = *rptr++;  /* left */
//			std::cout << "readptr:" << *rptr << std::endl;
//			std::cout << "recordedsamples:" << this->_data.recordedSamples[i] << std::endl;
//			std::cout << "writeptr:" << *wptr << std::endl;
			if( NUM_CHANNELS == 2 )
				*wptr++ = *rptr++;  /* right */
		}
	}
	this->_data.frameIndex += framesToCalc;
	return finished;
}

int PortAudioManager::recordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData)
{
	return ((PortAudioManager*)userData)->memberrecordCallback(inputBuffer, outputBuffer,
			framesPerBuffer, timeInfo, statusFlags, ((PortAudioManager*)userData)->getData());
}

paTestData			*PortAudioManager::getData()
{
	return &this->_data;
}

const std::string	&PortAudioManager::getError()
{
  this->_errorString = Pa_GetErrorText(this->_err);
  return this->_errorString;
}

PortAudioManager::~PortAudioManager()
{

}
