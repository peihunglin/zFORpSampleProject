#ifndef ZFP_BITSTREAM_H
#define ZFP_BITSTREAM_H

#include <stddef.h>

typedef struct bitstream bitstream;

bitstream* stream_open(void* buffer, size_t bufferSizeBytes);

void stream_close(bitstream* stream);

size_t stream_buffer_size(const bitstream* stream);

void stream_set_buffer_size(bitstream* stream, size_t bufferSizeBytes);

#endif
