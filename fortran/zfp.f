module zFORp_module

  use, intrinsic :: iso_c_binding, only: c_int, c_size_t, c_intptr_t, c_ptr, c_null_ptr
  implicit none
  private

  type zFORp_bitstream_type
    private
    type(c_ptr) :: object = c_null_ptr
    integer(c_size_t) :: bufferSizeBytes
  end type zFORp_bitstream_type

  interface
    ! bitstream

    function zfp_bitstream_stream_open(buffer, bufferSizeBytes) result(bitstream) bind(c, name="stream_open")
      import
      type(c_ptr), value :: buffer
      integer(c_size_t), value :: bufferSizeBytes
      integer(c_intptr_t) :: bitstream
    end function zfp_bitstream_stream_open

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
      integer(c_size_t) :: bufferSize
    end subroutine

  end interface

  ! type

  public :: zFORp_bitstream_type

  ! functions

  public :: zFORp_bitstream_stream_open, &
            zFORp_bitstream_stream_close, &
            zFORp_bitstream_stream_buffer_size, &
            zFORp_bitstream_stream_set_buffer_size

contains

! Fortran wrapper routines to interface C wrappers
  function zFORp_bitstream_stream_open(buffer, bufferSizeBytes) result(bitstream)
    implicit none
    type(c_ptr), intent(in) :: buffer
    integer, intent(in) :: bufferSizeBytes
    integer(c_intptr_t) :: bitstream

    bitstream%object = zfp_bitstream_stream_open(buffer, int(bufferSizeBytes, c_size_t))
  end function zFORp_bitstream_stream_open

  subroutine zFORp_bitstream_stream_close(bitstream)
    type(zFORp_bitstream_type), intent(inout) :: bitstream

    call zfp_bitstream_stream_close(bitstream%object)
    bitstream%object = c_null_ptr
  end subroutine zFORp_bitstream_stream_close

  function zFORp_bitstream_stream_buffer_size(bitstream) result(bufferSize)
    implicit none
    type(zFORp_bitstream_type), intent(in) :: bitstream
    integer :: bufferSize

    bufferSize = zfp_bitstream_stream_buffer_size(bitstream%object)
  end function zFORp_bitstream_stream_buffer_size

  subroutine zFORp_bitstream_stream_set_buffer_size(bitstream, bufferSize)
    type(zFORp_bitstream_type), intent(inout) :: bitstream
    integer, intent(in) :: bufferSize

    call zfp_bitstream_stream_set_buffer_size(bitstream%object, int(bufferSize, c_size_t))
  end subroutine zFORp_bitstream_stream_set_buffer_size

end module zFORp_module
