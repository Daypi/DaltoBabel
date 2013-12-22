/*
 * IAudioIO.hh
 *
 *  Created on: 9 déc. 2013
 *      Author: gambinn
 */

#ifndef IAUDIOIO_HH_
#define IAUDIOIO_HH_
#include <string>

class	IAudioIO {
public:
	virtual bool			init(void) = 0;
	virtual bool			cleanup(void) = 0;
	virtual bool			startRecording(void) = 0;
	virtual float			*paLoop(float *) = 0;
	virtual const std::string	&getError() = 0;
	virtual	~IAudioIO() {};
};

#endif /* IAUDIOIO_HH_ */
