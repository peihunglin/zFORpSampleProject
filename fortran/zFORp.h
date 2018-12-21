#include <stddef.h>

// bitstream

void*
zforp_bitstream_stream_open(void** buffer, size_t* bufferSizeBytes);

void*
zforp_bitstream_stream_open_default();

void*
zforp_bitstream_stream_open_test(void** buffer, size_t* bufferSizeBytes);

void
zforp_bitstream_stream_close(void** bitstream);

size_t
zforp_bitstream_buffer_size(void** bitstream);

void
zforp_bitstream_set_buffer_size(void** bitstream, size_t* bufferSizeBytes);
