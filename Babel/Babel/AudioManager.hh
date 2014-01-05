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
	void	setIn(unsigned char*, int);
	void	setOut();
	void			initLoop();
	void			recordAndPlay();
private:
	const float *	getRecord;
	bool			_isRecording;
	compressedFrame*		_in;
	compressedFrame*		_out;
	compressedFrame*		encode;
	float*			decode;
	PortAudioIO		_paio;
	ICompressor		*_compressor;
};