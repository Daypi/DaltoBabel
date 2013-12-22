/*
 * OpusCompressor.cpp
 *
 *  Created on: 8 déc. 2013
 *      Author: gambinn
 */

#include <iostream>
#include "OpusCompressor.hh"

OpusCompressor::OpusCompressor() {
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

unsigned char *OpusCompressor::encodeFrame(const float *frame, int frame_size)
{
	unsigned char *compressed_buffer;
	int ret;

	compressed_buffer = new (unsigned char[this->_encoded_data_size]);
	ret = opus_encode_float(this->_enc, frame, frame_size, compressed_buffer, this->_encoded_data_size);
	return (compressed_buffer);
}

float *OpusCompressor::decodeFrame(const unsigned char *data, int frame_size)
{
	int ret;
	float *frame = new (float[frame_size * this->_num_channels]);

	if (!opus_packet_get_nb_channels(data))
		return NULL;
	ret = opus_decode_float(this->_dec, data, this->_encoded_data_size, frame, frame_size, 0);
	return (frame);
}
