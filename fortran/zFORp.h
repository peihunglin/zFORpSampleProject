#include <stddef.h>

#include "fortranMacros.h"

// bitstream

void*
_prefixFOR(zforp_bitstream_stream_open)(void** buffer, size_t* bufferSizeBytes);

void
_prefixFOR(zforp_bitstream_stream_close)(void** bitstream);

size_t
_prefixFOR(zforp_bitstream_buffer_size)(void** bitstream);

void
_prefixFOR(zforp_bitstream_set_buffer_size)(void** bitstream, size_t* bufferSizeBytes);
