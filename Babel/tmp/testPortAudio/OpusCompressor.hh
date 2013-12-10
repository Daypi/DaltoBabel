/*
 * OpusCompressor.h
 *
 *  Created on: 8 déc. 2013
 *      Author: gambinn
 */

#ifndef OpusCompressor_HH_
#define OpusCompressor_HH_

#include "ICompressor.hh"
#include <opus/opus_defines.h>
#include <opus/opus.h>
#include <cstdlib>

class OpusCompressor {
private:
	int				_num_channels;
	int				_error;
	OpusEncoder		*_enc;
	OpusDecoder		*_dec;
	size_t			_encoded_data_size;

public:
	OpusCompressor(int, int);
	unsigned char	*encodeFrame(const float *, int);
	float			*decodeFrame(const unsigned char*, int);
	virtual ~OpusCompressor();
};

#endif /* OpusCompressor_HH_ */
