#include "Include/Network/AudioManager.hh"
#include "Include/Network/LibC.h"


AudioManager::AudioManager()
{
    this->_inIsUp = false;
	this->_isRecording = false;
	if (!this->_paio.init() || this->_paio.startRecording() == false)
		std::cout << "Portaudio init failed !" << std::endl;
	else
		std::cout << "Portaudio Initialised" << std::endl;
	this->_in = new compressedFrame;
	this->_out = new compressedFrame;
    this->_in->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
    this->_out->_frame = new unsigned char[NUM_CHANNELS * FRAMES_PER_BUFFER];
    LibC::memset(this->_in->_frame, 0, NUM_CHANNELS * FRAMES_PER_BUFFER);
    LibC::memset(this->_out->_frame, 0, NUM_CHANNELS * FRAMES_PER_BUFFER);
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
    LibC::memset(this->decode, 0, (NUM_CHANNELS * FRAMES_PER_BUFFER) * sizeof(float));
	this->_paio.paLoop();
}

unsigned char *AudioManager::recordAndPlay(int *ret)
{
	if ((this->_paio._err = Pa_IsStreamActive(this->_paio._Stream)) == 1)
	{
		if ((this->getRecord  = this->_paio.getRecord()) != NULL)
		{
			if (decode != NULL)
			{
				this->_out = this->_compressor->encodeFrame(this->getRecord , encode);
                //this->_in = this->_out;
                if (this->_inIsUp == true)
                {
                    _compressor->decodeFrame(_in, this->decode);
                    this->_paio.setPlay(this->decode, 480);
                    this->_inIsUp = false;
                }
			}
			else
			{
				this->_out = this->_compressor->encodeFrame(this->getRecord, encode);
                //this->_in = this->_out;
				_compressor->decodeFrame(_in, decode);
            }
            *ret = this->_out->_size;
		}
        else
            *ret = 0;
	}

    return (this->_out->_frame);
}

void AudioManager::setIn(const unsigned char * buffer, int i)
{
    std::cout << "setin" << std::endl;
    this->_in->_frame = const_cast<unsigned char *>(buffer);
	this->_in->_size = i;
    this->_inIsUp = true;
}

void AudioManager::setOut()
{

}

void AudioManager::setPlayback(bool playback)
{
    this->_paio.setPlayback(playback);
}

AudioManager::~AudioManager()
{
}
