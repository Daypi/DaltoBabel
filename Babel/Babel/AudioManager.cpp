#include "AudioManager.hh"


AudioManager::AudioManager()
{
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
}

void AudioManager::mainLoop()
{
	float *temp;
	int frameSize = NUM_SECONDS * SAMPLE_RATE;
	while (42)
	{
		this->_paio.paLoop(temp);
//		_opus.encodeFrame(this->_paio.paLoop(_opus.decodeFrame(const_cast<const unsigned char *>(_in), frameSize)), frameSize);
	}
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