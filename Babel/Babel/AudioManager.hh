#pragma once

#include <iostream>
#include <string>
#include <list>
#include <portaudio.h>
#include "PortAudioIO.hh"
#include "OpusCompressor.hh"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void	mainLoop();
	void	setIn();
	void	setOut();
private:
	unsigned char*			_in;
	unsigned char*			_out;
	PortAudioIO		_paio;
	//OpusCompressor	_opus;
};