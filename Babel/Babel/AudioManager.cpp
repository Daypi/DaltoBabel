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
	this->_paio.paLoop(temp);
		while( ( this->_paio._err = Pa_IsStreamActive(this->_paio._Stream) ) == 1)
	{
//		std::cout << "1" << std::endl;
		if (this->_paio.getRecord() != NULL)
		{
			if (temp != NULL)
			{
				temp = _opus.decodeFrame(const_cast<const unsigned char *>(_in), frameSize);
				this->_out =_opus.encodeFrame(this->_paio.getRecord(), frameSize);
				std::cout << "KOUK" << std::endl;
				this->_paio.setPlay(temp, 480);
				this->_in = this->_out;
			}
			else
			{
				temp = new float[100];
				this->_out =_opus.encodeFrame(this->_paio.getRecord(), frameSize);
				this->_in = this->_out;
				std::cout << "Jouge" << std::endl; 
			}
		}
	}
	delete temp;
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