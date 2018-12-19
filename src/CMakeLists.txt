add_library(zfp bitstream.c)

target_compile_definitions(zfp PRIVATE ${zfp_defs})

target_include_directories(zfp
  PUBLIC
    $<BUILD_INTERFACE:${ZFP_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
