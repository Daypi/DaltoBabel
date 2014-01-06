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
    void	setIn(const unsigned char*, int);
	void	setOut();
	void			initLoop();
    void            setPlayback(bool);
    unsigned char *			recordAndPlay(int *);
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
