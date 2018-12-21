#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// avoid using any zfp-defined types (bitstream) or API functions
// use void* when interfacing with Fortran
#include "bitstream.h"

// enables calling Fortran API
#include "zFORp.h"

void
assert_zforp_bitstream_contents(zforp_bitstream_type* zbs, void* buffer, size_t bufferSizeBytes)
{
  void* observedBuffer = zforp_bitstream_stream_buffer_ptr(zbs);
  assert(observedBuffer == buffer);

  size_t observedBufferSizeBytes = zforp_bitstream_stream_buffer_size(zbs);
  assert(observedBufferSizeBytes == bufferSizeBytes);
}

void
assert_zforp_bitstream_closed(zforp_bitstream_type* zbs)
{
  assert(zbs->stream == NULL);
}

int main()
{
  size_t bufferSizeBytes = 5;

  // Method 1: call C library directly when allocating a bitstream
  //           and close it through the Fortran wrapper function
  printf("Method 1\n");

  void* buffer1 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer1 == NULL) {
    printf("Failed to allocate memory for buffer1\n");
    return 1;
  }

  zforp_bitstream_type zbs1;
  zbs1.stream = stream_open(buffer1, bufferSizeBytes);
  assert_zforp_bitstream_contents(&zbs1, buffer1, bufferSizeBytes);

  zforp_bitstream_stream_close(&zbs1);
  assert_zforp_bitstream_closed(&zbs1);

  // Method 2: call Fortran wrapper functions to open & close a bitstream
  printf("Method 2\n");

  void* buffer2 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer2 == NULL) {
    printf("Failed to allocate memory for buffer2\n");
    return 1;
  }

  zforp_bitstream_type zbs2 = zforp_bitstream_stream_open(&buffer2, &bufferSizeBytes);
  assert_zforp_bitstream_contents(&zbs2, buffer2, bufferSizeBytes);

  zforp_bitstream_stream_close(&zbs2);
  assert_zforp_bitstream_closed(&zbs2);

  // Method 3: call Fortran wrappers, using subroutine version of stream_open
  printf("Method 3\n");

  void* buffer3 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer3 == NULL) {
    printf("Failed to allocate memory for buffer3\n");
    return 1;
  }

  zforp_bitstream_type zbs3;
  zforp_bitstream_stream_open_subroutine(&zbs3, &buffer3, &bufferSizeBytes);
  assert_zforp_bitstream_contents(&zbs3, buffer3, bufferSizeBytes);

  zforp_bitstream_stream_close(&zbs3);
  assert_zforp_bitstream_closed(&zbs3);

  // Method 4: call Fortran wrappers, using default version of stream_open,
  //           and setting initial values after-the-fact
  printf("Method 4\n");

  void* buffer4 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer4 == NULL) {
    printf("Failed to allocate memory for buffer4\n");
    return 1;
  }

  zforp_bitstream_type zbs4 = zforp_bitstream_stream_open_default();
  zforp_bitstream_stream_set_buffer_ptr(&zbs4, &buffer4);
  zforp_bitstream_stream_set_buffer_size(&zbs4, &bufferSizeBytes);
  assert_zforp_bitstream_contents(&zbs4, buffer4, bufferSizeBytes);

  zforp_bitstream_stream_close(&zbs4);
  assert_zforp_bitstream_closed(&zbs4);

  free(buffer1);
  free(buffer2);
  free(buffer3);
  free(buffer4);

  return 0;
}
