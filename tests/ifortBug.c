#include <stdlib.h>
#include <stdio.h>

// avoid using any zfp-defined types (bitstream) or API functions
// use void* when interfacing with Fortran
#include "bitstream.h"

// enables calling Fortran API
#include "zFORp.h"

int main()
{
  size_t bufferSizeBytes = 5;

  // Two issues, both seen in func zforp_bitstream_stream_open(), in Method 2

  // Method 1: call C library directly when allocating a bitstream
  //           and close it through the Fortran wrapper function

  void* buffer1 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer1 == NULL) {
    printf("Failed to allocate memory for buffer1\n");
    return 1;
  }

  // works, leak free
  void* bitstream1 = stream_open(buffer1, bufferSizeBytes);
  _prefixFOR(zforp_bitstream_stream_close)(&bitstream1);

  free(buffer1);

  // Method 2: call Fortran wrapper functions to open & close a bitstream

  void* buffer2 = calloc(bufferSizeBytes, sizeof(char));
  if (buffer2 == NULL) {
    printf("Failed to allocate memory for buffer2\n");
    return 1;
  }

  // Issue A: icc/ifort corrupts passed-in arguments
  //          (step into Fortran code with gdb and observe)

  // Issue B: icc/ifort returns a "ptr to a ptr to a bitstream-ptr"
  //          while gcc/gfort returns a "ptr to a bitstream-ptr"
  //          (some ambiguity on whether zFORp_bitstream_type is returned, or its content, "object")

  void* bitstream2 = _prefixFOR(zforp_bitstream_stream_open)(&buffer2, &bufferSizeBytes);
  _prefixFOR(zforp_bitstream_stream_close)(&bitstream2);

  free(buffer2);

  return 0;
}
