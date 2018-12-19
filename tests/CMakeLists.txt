enable_language(Fortran)

if(CMAKE_Fortran_COMPILER_ID MATCHES "GNU")
  set(dialect "-ffree-form -std=f2008 -fimplicit-none")
  set(bounds "-fbounds-check")
endif()
if(CMAKE_Fortran_COMPILER_ID MATCHES "Intel")
  set(dialect "-stand f08 -free -implicitnone")
  set(bounds "-check bounds")
endif()

set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/modules)
set(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} ${bounds}")
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${dialect}")

add_executable(ifortBug ifortBug.c)
target_link_libraries(ifortBug zfp zFORp)
add_test(NAME ifortBug COMMAND ifortBug)

add_executable(zforpBitstream zforpBitstream.c)
target_link_libraries(zforpBitstream zfp zFORp)
add_test(NAME zforpBitstream COMMAND zforpBitstream)
