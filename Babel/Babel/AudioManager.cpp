#include "AudioManager.hh"


AudioManager::AudioManager()
{
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
	this->_in = new unsigned char[NUM_CHANNELS * NUM_SECONDS * SAMPLE_RATE];
	this->_out = new unsigned char[NUM_CHANNELS * NUM_SECONDS * SAMPLE_RATE];

}

void AudioManager::mainLoop()
{
	const float *temp2;
	int frameSize = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
	this->_isRecording = true;
	unsigned char *encode = new unsigned char[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS];
	float *decode = new float[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS];
	decode = NULL;
	this->_paio.paLoop(decode);
	std::cout << "___________START LOOP___________" << std::endl;
		while( ( this->_paio._err = Pa_IsStreamActive(this->_paio._Stream) ) == 1)
	{
		if ((temp2 = this->_paio.getRecord()) != NULL)
		{
/*			std::cout << "coucou" << std::endl;
			if (decode != NULL)
			{
				printf("N AM: %f\n", temp2[0]);
				this->_out = this->_opus.encodeFrame(temp2, encode);
				this->_in = this->_out;
				_opus.decodeFrame(const_cast<const unsigned char *>(_in), decode);*/
				this->_paio.setPlay(const_cast<float *>(temp2), 480);
/*			}
			else
			{
				printf("F AM: %f\n", temp2[0]);
				this->_out = this->_opus.encodeFrame(temp2, encode);
				//std::cout << this->_out << std::endl;
				this->_in = this->_out;
				_opus.decodeFrame(const_cast<const unsigned char *>(_in), decode);
			}*/
		}
	}
	delete decode;
	delete encode;
}

void AudioManager::setIn()
{

}

void AudioManager::setOut()
{

}

AudioManager::~AudioManager()
{
}