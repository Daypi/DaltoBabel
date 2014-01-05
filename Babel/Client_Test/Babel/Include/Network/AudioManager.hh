#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Include/Network/portaudio.h"
#include "PortAudioIO.hh"
#include "OpusCompressor.hh"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void	mainLoop();
	void	setIn(unsigned char*, int);
	void	setOut();
	void			initLoop();
	void			recordAndPlay();
private:
	const float *	getRecord;
	bool			_isRecording;
	opusFrame*		_in;
	opusFrame*		_out;
	opusFrame*		encode;
	float*			decode;
	PortAudioIO		_paio;
	OpusCompressor	_opus;
};
