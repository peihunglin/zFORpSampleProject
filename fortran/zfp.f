module zFORp_module

  use, intrinsic :: iso_c_binding, only: c_int, c_size_t, c_intptr_t, c_ptr, c_null_ptr
  implicit none
  private

  type, bind(c) :: zFORp_bitstream_type
    private
    type(c_ptr) :: object = c_null_ptr
  end type zFORp_bitstream_type

  interface
    ! bitstream

    function zfp_bitstream_stream_open(buffer, bufferSizeBytes) result(bitstream) bind(c, name="stream_open")
      import
      type(c_ptr), value :: buffer
      integer(c_size_t), value :: bufferSizeBytes
      type(c_ptr) :: bitstream
    end function zfp_bitstream_stream_open

    function zfp_bitstream_stream_open_default() result(bitstream) bind(c, name="stream_open_default")
      import
      type(c_ptr) :: bitstream
    end function zfp_bitstream_stream_open_default

    subroutine zfp_bitstream_stream_close(bitstream) bind(c, name="stream_close")
      import
      type(c_ptr), value :: bitstream
    end subroutine

    function zfp_bitstream_stream_buffer_size(bitstream) result(bufferSize) bind(c, name="stream_buffer_size")
      import
      type(c_ptr), value :: bitstream
      integer(c_size_t) :: bufferSize
    end function

    subroutine zfp_bitstream_stream_set_buffer_size(bitstream, bufferSize) bind(c, name="stream_set_buffer_size")
      import
      type(c_ptr), value :: bitstream
      integer(c_size_t), value :: bufferSize
    end subroutine

    function zfp_bitstream_stream_buffer_ptr(bitstream) result(bufferPtr) bind(c, name="stream_buffer_ptr")
      import
      type(c_ptr), value :: bitstream
      type(c_ptr) :: bufferPtr
    end function

    subroutine zfp_bitstream_stream_set_buffer_ptr(bitstream, bufferPtr) bind(c, name="stream_set_buffer_ptr")
      import
      type(c_ptr), value :: bitstream, bufferPtr
    end subroutine

    subroutine zfp_dump_c_pointer(ptr1, ptr2) bind(c, name="dump_c_ptr")
      import
      type(c_ptr), value :: ptr1
      type(c_ptr) :: ptr2
    end subroutine

  end interface

  ! type

  public :: zFORp_bitstream_type

  ! functions

  public :: zFORp_bitstream_stream_open, &
            zFORp_bitstream_stream_open_default, &
            zFORp_bitstream_stream_open_test, &
            zFORp_bitstream_stream_close, &
            zFORp_bitstream_stream_buffer_size, &
            zFORp_bitstream_stream_set_buffer_size, &
            zFORp_bitstream_stream_buffer_ptr, &
            zFORp_bitstream_stream_set_buffer_ptr

contains

! Fortran wrapper routines to interface C wrappers
  function zFORp_bitstream_stream_open(buffer, bufferSizeBytes) result(bitstream) &
    bind(c,name="zforp_bitstream_stream_open")
    implicit none
    type(c_ptr), intent(in) :: buffer
    integer, intent(in) :: bufferSizeBytes
    type(zFORp_bitstream_type) :: bitstream

    bitstream%object = zfp_bitstream_stream_open(buffer, int(bufferSizeBytes, c_size_t))
  end function zFORp_bitstream_stream_open

  subroutine zFORp_bitstream_stream_open_subroutine(bitstream, buffer, bufferSizeBytes) &
    bind(c,name="zforp_bitstream_stream_open_subroutine")
    implicit none
    type(c_ptr), intent(in) :: buffer
    integer, intent(in) :: bufferSizeBytes
    type(zFORp_bitstream_type), intent(inout) :: bitstream

    bitstream%object = zfp_bitstream_stream_open(buffer, int(bufferSizeBytes, c_size_t))
  end subroutine zFORp_bitstream_stream_open_subroutine

  function zFORp_bitstream_stream_open_default() result(bitstream) &
    bind(c,name="zforp_bitstream_stream_open_default")
    implicit none
    type(zFORp_bitstream_type) :: bitstream

    bitstream%object = zfp_bitstream_stream_open_default()
  end function zFORp_bitstream_stream_open_default

  function zFORp_bitstream_stream_open_test(buffer, bufferSizeBytes) result(bitstream) &
    bind(c,name="zforp_bitstream_stream_open_test")
    implicit none
    type(c_ptr), intent(in),value :: buffer
    integer, intent(in) :: bufferSizeBytes
    type(zFORp_bitstream_type) :: bitstream

    bitstream%object = zfp_bitstream_stream_open(buffer, int(bufferSizeBytes, c_size_t))
  end function zFORp_bitstream_stream_open_test

  subroutine zFORp_bitstream_stream_close(bitstream) & 
    bind(c,name="zforp_bitstream_stream_close")
    type(zFORp_bitstream_type), intent(inout) :: bitstream

    call zfp_bitstream_stream_close(bitstream%object)
    bitstream%object = c_null_ptr
  end subroutine zFORp_bitstream_stream_close

  function zFORp_bitstream_stream_buffer_size(bitstream) result(bufferSize) &
    bind(c,name="zforp_bitstream_stream_buffer_size")
    implicit none
    type(zFORp_bitstream_type), intent(in) :: bitstream
    integer :: bufferSize

    bufferSize = zfp_bitstream_stream_buffer_size(bitstream%object)
  end function zFORp_bitstream_stream_buffer_size

  subroutine zFORp_bitstream_stream_set_buffer_size(bitstream, bufferSize) &
    bind(c,name="zforp_bitstream_stream_set_buffer_size")
    type(zFORp_bitstream_type), intent(inout) :: bitstream
    integer, intent(in) :: bufferSize

    call zfp_bitstream_stream_set_buffer_size(bitstream%object, int(bufferSize, c_size_t))
  end subroutine zFORp_bitstream_stream_set_buffer_size

  function zFORp_bitstream_stream_buffer_ptr(bitstream) result(bufferPtr) &
    bind(c,name="zforp_bitstream_stream_buffer_ptr")
    implicit none
    type(zFORp_bitstream_type), intent(in) :: bitstream
    type(c_ptr) :: bufferPtr

    bufferPtr = zfp_bitstream_stream_buffer_ptr(bitstream%object)
  end function zFORp_bitstream_stream_buffer_ptr

  subroutine zFORp_bitstream_stream_set_buffer_ptr(bitstream, bufferPtr) &
    bind(c,name="zforp_bitstream_stream_set_buffer_ptr")
    type(zFORp_bitstream_type), intent(inout) :: bitstream
    type(c_ptr), intent(in) :: bufferPtr

    call zfp_bitstream_stream_set_buffer_ptr(bitstream%object, bufferPtr)
  end subroutine zFORp_bitstream_stream_set_buffer_ptr

end module zFORp_module
