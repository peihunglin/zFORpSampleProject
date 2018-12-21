#include <stddef.h>

// bitstream

typedef struct zforp_bitstream_type zforp_bitstream_type;

struct zforp_bitstream_type {
  void* stream;
};

zforp_bitstream_type
zforp_bitstream_stream_open(void** buffer, size_t* bufferSizeBytes);

void
zforp_bitstream_stream_open_subroutine(zforp_bitstream_type* bitstream, void** buffer, size_t* bufferSizeBytes);

zforp_bitstream_type
zforp_bitstream_stream_open_default();

zforp_bitstream_type*
zforp_bitstream_stream_open_test(void** buffer, size_t* bufferSizeBytes);

void
zforp_bitstream_stream_close(zforp_bitstream_type* bitstream);

size_t
zforp_bitstream_stream_buffer_size(const zforp_bitstream_type* bitstream);

void
zforp_bitstream_stream_set_buffer_size(zforp_bitstream_type* bitstream, size_t* bufferSizeBytes);

void*
zforp_bitstream_stream_buffer_ptr(const zforp_bitstream_type* bitstream);

void
zforp_bitstream_stream_set_buffer_ptr(zforp_bitstream_type* bitstream, void* bufferPtr);
