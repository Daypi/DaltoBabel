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

compressedFrame *OpusCompressor::encodeFrame(const float *frame, compressedFrame *compressed_buffer)
{
	int ret;

	printf("encoding.\n");
	/*for (int i = 0 ; i < 200 ; i++)
		printf("OPUS enc: %f\n", frame[i]);*/
	//compressed_buffer->_frame = new (unsigned char[this->_maxSize]);
	ret = opus_encode_float(this->_enc, frame, FRAMES_PER_BUFFER, compressed_buffer->_frame, this->_encoded_data_size);
	std::cout << "ret:" << ret << std::endl;
	
	compressed_buffer->_size = ret;
	return (compressed_buffer);
}

float *OpusCompressor::decodeFrame(const compressedFrame *data, float *frame)
{
	int ret;
	printf("decoding.\n");
	//printf("OPUS dec: %s\n", data->_frame);
	std::cout << "size:" << data->_size << std::endl;
	std::cout << "encoded data size: " << this->_encoded_data_size << std::endl;
	frame = new (float[this->_encoded_data_size]);
	ret = opus_decode_float(this->_dec, data->_frame, this->_encoded_data_size, frame, FRAMES_PER_BUFFER, 0);
	std::cout << "ret:" << ret << std::endl;
	return (frame);
}
