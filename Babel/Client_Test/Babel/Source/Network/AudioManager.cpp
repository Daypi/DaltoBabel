#include "Include/Network/AudioManager.hh"


AudioManager::AudioManager()
{
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
	this->_in = new opusFrame;
	this->_out = new opusFrame;
    this->_in->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
    this->_out->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];

}

void AudioManager::mainLoop()
{

	this->initLoop();
		while ( ( this->_paio._err =  Pa_IsStreamActive(this->_paio._Stream ) ) == 1)
	{
		if ((this->getRecord = this->_paio.getRecord()) != NULL)
		{
			if (decode != NULL)
			{
				this->_out = this->_opus.encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
				_opus.decodeFrame(_in, decode);
				this->_paio.setPlay(const_cast<float *>(this->getRecord), 480);
			}
			else
			{
				this->_out = this->_opus.encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
                _opus.decodeFrame(_in, decode);
            }
		}
	}

}

void AudioManager::initLoop()
{
		const float *temp2;
    int frameSize = FRAMES_PER_BUFFER * NUM_CHANNELS;
	this->_isRecording = true;

	this->encode = new opusFrame;
    encode->_frame = new unsigned char[FRAMES_PER_BUFFER * NUM_CHANNELS];
    this->decode = new float[FRAMES_PER_BUFFER * NUM_CHANNELS];
	this->_paio.paLoop();
}

void AudioManager::recordAndPlay()
{
	if ((this->_paio._err = Pa_IsStreamActive(this->_paio._Stream)) == 1)
	{
		if ((this->getRecord  = this->_paio.getRecord()) != NULL)
		{
			if (decode != NULL)
			{
				this->_out = this->_opus.encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
				_opus.decodeFrame(_in, decode);
				this->_paio.setPlay(const_cast<float *>(this->getRecord), 480);
			}
			else
			{
				this->_out = this->_opus.encodeFrame(this->getRecord, encode);
				this->_in = this->_out;
				_opus.decodeFrame(_in, decode);
			}
		}
	}

}

void AudioManager::setIn(unsigned char * buffer, int i)
{
	this->_in->_frame = buffer;
	this->_in->_size = i;
}

void AudioManager::setOut()
{

}

AudioManager::~AudioManager()
{
}
