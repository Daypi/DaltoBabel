/*
 * OpusCompressor.cpp
 *
 *  Created on: 8 déc. 2013
 *      Author: gambinn
 */

#include <iostream>
#include "Include/Network/OpusCompressor.hh"

OpusCompressor::OpusCompressor()
{
	this->_maxSize = MAX_SIZE;
	this->_num_channels = NUM_CHANNELS;
	this->_enc = opus_encoder_create(SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &this->_error);
	this->_dec = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &this->_error);
	opus_int32 rate;
	opus_encoder_ctl(this->_enc, OPUS_GET_BANDWIDTH(&rate));
	this->_encoded_data_size = rate;
}


OpusCompressor::~OpusCompressor() {
    opus_encoder_destroy(this->_enc);
    opus_decoder_destroy(this->_dec);
}

opusFrame *OpusCompressor::encodeFrame(const float *frame, opusFrame *compressed_buffer)
{
	int ret;

	ret = opus_encode_float(this->_enc, frame, FRAMES_PER_BUFFER, compressed_buffer->_frame, this->_encoded_data_size);
	std::cout << "ret:" << ret << std::endl;
	
	compressed_buffer->_size = ret;
	return (compressed_buffer);
}

float *OpusCompressor::decodeFrame(const opusFrame *data, float *frame)
{
	int ret;

	frame = new (float[this->_encoded_data_size]);
	ret = opus_decode_float(this->_dec, data->_frame, this->_encoded_data_size, frame, FRAMES_PER_BUFFER, 0);
	return (frame);
}
