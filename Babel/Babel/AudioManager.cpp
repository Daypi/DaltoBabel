#include "AudioManager.hh"


AudioManager::AudioManager()
{
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
}

void AudioManager::mainLoop()
{
	float *temp;
	int frameSize = 100;//NUM_SECONDS * SAMPLE_RATE;
	this->_isRecording = true;
	this->_in = NULL;
	this->_out = NULL;
	temp = NULL;
	while (this->_isRecording)
	{
		if (temp != NULL)
		{
			std::cout << "NARMOL" << std::endl;
			temp = _opus.decodeFrame(const_cast<const unsigned char *>(_in), frameSize);
//		this->_paio.paLoop(&temp);
		std::cout << "decoded" << std::endl;
		this->_out =_opus.encodeFrame(this->_paio.paLoop(temp), frameSize);
		this->_in = this->_out;
		}
		else
		{
			std::cout << "INIET" << std::endl;
			temp = new float[100];
			this->_out =_opus.encodeFrame(this->_paio.paLoop(temp), frameSize);
			this->_in = this->_out;
			delete temp;
		}
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