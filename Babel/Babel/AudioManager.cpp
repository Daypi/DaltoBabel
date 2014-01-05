#include "AudioManager.hh"


AudioManager::AudioManager()
{
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
	this->_in = new opusFrame;
	this->_out = new opusFrame;
	this->_in->_frame = new unsigned char[NUM_CHANNELS * NUM_SECONDS * SAMPLE_RATE];
	this->_out->_frame = new unsigned char[NUM_CHANNELS * NUM_SECONDS * SAMPLE_RATE];

}

void AudioManager::mainLoop()
{

	this->initLoop();
	std::cout << "___________START LOOP___________" << std::endl;
		while ( ( this->_paio._err =  Pa_IsStreamActive(this->_paio._Stream ) ) == 1)
	{
		if ((this->getRecord = this->_paio.getRecord()) != NULL)
		{
			std::cout << "coucou" << std::endl;
			if (decode != NULL)
			{
				printf("N AM: %f\n", this->getRecord [0]);
				this->_out = this->_opus.encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
				_opus.decodeFrame(_in, decode);
				this->_paio.setPlay(const_cast<float *>(this->getRecord), 480);
			}
			else
			{
				printf("F AM: %f\n", this->getRecord [0]);
				this->_out = this->_opus.encodeFrame(this->getRecord , encode);
				//std::cout << this->_out << std::endl;
				this->_in = this->_out;
				_opus.decodeFrame(_in, decode);
				//this->_paio.setPlay(const_cast<float *>(decode), 480);
			}
		}
	}

}

void AudioManager::initLoop()
{
		const float *temp2;
	int frameSize = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
	this->_isRecording = true;

	this->encode = new opusFrame;
	encode->_frame = new unsigned char[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS];
	this->decode = new float[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS];
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