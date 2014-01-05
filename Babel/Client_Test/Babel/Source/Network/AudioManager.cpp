#include "Include/Network/AudioManager.hh"


AudioManager::AudioManager()
{
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
	this->_in = new compressedFrame;
	this->_out = new compressedFrame;
    this->_in->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
    this->_out->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
	this->_compressor = new OpusCompressor;
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
				this->_out = this->_compressor->encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
				_compressor->decodeFrame(_in, decode);
				this->_paio.setPlay(const_cast<float *>(this->getRecord), 480);
			}
			else
			{
				this->_out = this->_compressor->encodeFrame(this->getRecord , encode);
				//std::cout << this->_out << std::endl;
				this->_in = this->_out;
				_compressor->decodeFrame(_in, decode);
				//this->_paio.setPlay(const_cast<float *>(decode), 480);
			}
		}
	}

}

void AudioManager::initLoop()
{
		const float *temp2;
    int frameSize = NUM_CHANNELS * FRAMES_PER_BUFFER;
	this->_isRecording = true;

	this->encode = new compressedFrame;
    encode->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
    this->decode = new float[NUM_CHANNELS * FRAMES_PER_BUFFER];
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
				this->_out = this->_compressor->encodeFrame(this->getRecord , encode);
				this->_in = this->_out;
				_compressor->decodeFrame(_in, decode);
				this->_paio.setPlay(const_cast<float *>(this->getRecord), 480);
			}
			else
			{
				this->_out = this->_compressor->encodeFrame(this->getRecord, encode);
				this->_in = this->_out;
				_compressor->decodeFrame(_in, decode);
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
