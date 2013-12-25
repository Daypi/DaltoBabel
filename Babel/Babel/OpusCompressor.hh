/*
 * OpusCompressor.h
 *
 *  Created on: 8 déc. 2013
 *      Author: gambinn
 */

#ifndef OpusCompressor_HH_
#define OpusCompressor_HH_

#include "ICompressor.hh"
#include <opus_defines.h>
#include <opus.h>
#include <cstdlib>
#include "babel_common.h"

#define		MAX_SIZE 1000

class OpusCompressor {
private:
	int				_num_channels;
	int				_error;
	OpusEncoder		*_enc;
	OpusDecoder		*_dec;
	size_t			_encoded_data_size;
	size_t			_maxSize;
public:
	OpusCompressor();
	unsigned char	*encodeFrame(const float *, unsigned char*);
	float			*decodeFrame(const unsigned char*, float *);
	virtual ~OpusCompressor();
};

#endif /* OpusCompressor_HH_ */
