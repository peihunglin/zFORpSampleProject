#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitstream.h"

struct bitstream {
  void* buffer;
  size_t bufferSizeBytes;
};

/* allocate and initialize bit stream to user-allocated buffer */
bitstream*
stream_open(void* buffer, size_t bufferSizeBytes)
{
  printf("C buffer pointer in C API: %p\n", buffer);
  bitstream* stream = (bitstream*)malloc(sizeof(bitstream));
  if (stream) {
    stream->buffer = buffer;
    stream->bufferSizeBytes = bufferSizeBytes;
  }
  printf("C stream pointer in C API: %p\n", stream);
  return stream;
}

/* close and deallocate bit stream */
void
stream_close(bitstream* stream)
{
  free(stream);
}

size_t
stream_buffer_size(const bitstream* stream)
{
  if (stream) {
    return stream->bufferSizeBytes;
  }

  return 0;
}

void
stream_set_buffer_size(bitstream* stream, size_t bufferSizeBytes)
{
  if(stream) {
    stream->bufferSizeBytes = bufferSizeBytes;
  }
}

void dump_c_ptr(void* ptr1, void* ptr2)
{
  printf("C pointer value in C API by value: %p by address: %p\n", ptr1, ptr2);
}

