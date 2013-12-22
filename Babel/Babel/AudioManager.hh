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

private:
	PortAudioIO		_paio;
	//OpusCompressor	_opus;
};