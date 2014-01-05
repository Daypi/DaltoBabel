/*
 * ICompressor.hh
 *
 *  Created on: 9 déc. 2013
 *      Author: gambinn
 */

#ifndef ICOMPRESSOR_HH_
#define ICOMPRESSOR_HH_

typedef struct s_compressedFrame {
	unsigned char	*_frame;
	int				_size;
} compressedFrame;

class	ICompressor {
public:
	virtual compressedFrame *encodeFrame(const float *, compressedFrame*) = 0;
	virtual float			*decodeFrame(const compressedFrame*, float *) = 0;
	virtual	~ICompressor() {};
};

#endif /* ICOMPRESSOR_HH_ */
