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
	bool					_isRecording;
	opusFrame*			_in;
	opusFrame*			_out;
	PortAudioIO		_paio;
	OpusCompressor	_opus;
};