#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "bitstream.h"

// enables calling Fortran API (commented out below)
#include "zFORp.h"

int main()
{
  // setup

  size_t initialBufferSizeBytes = 5;
  void* buffer = calloc(initialBufferSizeBytes, sizeof(char));
  if (buffer == NULL) {
    printf("Failed to allocate memory for buffer\n");
    return 1;
  }

  bitstream* bs = stream_open(buffer, initialBufferSizeBytes);

  // test assertions
  // (would like to automatically substitute fortran wrappers in place of C API calls)
  assert(stream_buffer_size(bs) == initialBufferSizeBytes);
//  assert(_prefixFOR(zforp_bitstream_stream_buffer_size)(&bs) == initialBufferSizeBytes);

  size_t newBufferSizeBytes = 11;
  stream_set_buffer_size(bs, newBufferSizeBytes);
//  _prefixFOR(zforp_bitstream_stream_set_buffer_size)(&bs, &newBufferSizeBytes);

  assert(stream_buffer_size(bs) == newBufferSizeBytes);
//  assert(_prefixFOR(zforp_bitstream_stream_buffer_size)(&bs) == newBufferSizeBytes);

  // finish, free
  stream_close(bs);
  free(buffer);

  return 0;
}
