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
  printf("test1: buffer 1 address = %p\n",buffer1);
  if (buffer1 == NULL) {
    printf("Failed to allocate memory for buffer1\n");
    return 1;
  }

  // works, leak free
  void* bitstream1 = stream_open(buffer1, bufferSizeBytes);
  printf("test1: returned bitstream1 address = %p\n",bitstream1);
  zforp_bitstream_stream_close(&bitstream1);


  // Method 2: call Fortran wrapper functions to open & close a bitstream

  void* buffer2 = calloc(bufferSizeBytes, sizeof(char));
  printf("\ntest2: buffer 2 address = %p\n",buffer2);
  if (buffer2 == NULL) {
    printf("Failed to allocate memory for buffer2\n");
    return 1;
  }

  // Issue A: icc/ifort corrupts passed-in arguments
  //          (step into Fortran code with gdb and observe)

  // Issue B: icc/ifort returns a "ptr to a ptr to a bitstream-ptr"
  //          while gcc/gfort returns a "ptr to a bitstream-ptr"
  //          (some ambiguity on whether zFORp_bitstream_type is returned, or its content, "object")

  void* bitstream2 = zforp_bitstream_stream_open(&buffer2, &bufferSizeBytes);
  printf("test1: returned bitstream2 address = %p\n",bitstream2);
  zforp_bitstream_stream_close(&bitstream2);


  void* buffer3 = calloc(bufferSizeBytes, sizeof(char));
  printf("\ntest3: buffer 3 address = %p\n",buffer3);
  if (buffer3 == NULL) {
    printf("Failed to allocate memory for buffer3\n");
    return 1;
  }

  void* bitstream3 = zforp_bitstream_stream_open_test(buffer3, &bufferSizeBytes);
  printf("test1: returned bitstream3 address = %p\n",bitstream3);
  zforp_bitstream_stream_close(&bitstream3);

  free(buffer1);
  free(buffer2);
  free(buffer3);

  return 0;
}
