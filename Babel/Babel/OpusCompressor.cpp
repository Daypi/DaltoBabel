/*
 * OpusCompressor.cpp
 *
 *  Created on: 8 déc. 2013
 *      Author: gambinn
 */

#include <iostream>
#include "OpusCompressor.hh"

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

	printf("encoding.\n");
	printf("OPUS enc: %f\n", frame[0]);
//	compressed_buffer = new (unsigned char[this->_maxSize]);
	ret = opus_encode_float(this->_enc, frame, SAMPLE_RATE, compressed_buffer->_frame, this->_maxSize);
	compressed_buffer->_size = ret;
	return (compressed_buffer);
}

float *OpusCompressor::decodeFrame(const opusFrame *data, float *frame)
{
	int ret;
//	float *frame = new (float[frame_size * this->_num_channels]);
	printf("decoding.\n");
	printf("OPUS dec: %c\n", data[0]);
	if (!opus_packet_get_nb_channels(data->_frame))
		return NULL;
	ret = opus_decode_float(this->_dec, data->_frame, data->_size, frame, SAMPLE_RATE, 0);
	return (frame);
}
