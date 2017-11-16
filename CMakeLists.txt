cmake_minimum_required(VERSION 2.6.0)

################################################################## MAC USER ##################################################################
#if(APPLE)
#  SET(CMAKE_CXX_ARCHIVE_CREATE "/usr/bin/libtool -v -o <TARGET><LINK_FLAGS> <OBJECTS>")
#  SET(CMAKE_C_ARCHIVE_CREATE "/usr/bin/libtool -v -o <TARGET>
#<LINK_FLAGS> <OBJECTS>")
#endif()

########################################
#  Magick++
########################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})

find_file(MAGICK_CONFIG_EXE "Magick++-config" PATHS
    "/usr/bin"
    "/usr/local/bin"
)
if (MAGICK_CONFIG_EXE)
  message(STATUS "Found Image Magick++ libaries -- Enabling MagickPainter.")
  execute_process(COMMAND Magick++-config --cppflags OUTPUT_VARIABLE Magick_CPP_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --cxxflags OUTPUT_VARIABLE Magick_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --ldflags  OUTPUT_VARIABLE Magick_LD_FLAGS  OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --libs     OUTPUT_VARIABLE Magick_LIBS      OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Magick_CPP_FLAGS} ${Magick_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Magick_LIBS} ${Magick_LD_FLAGS}")
  
#  add_definitions(-DUSE_MAGICK_PAINTER)
#  set(obdepict_srcs ${depict_srcs} src/magickpainter.cpp tools/magickdepict.cpp)
#
#  add_executable(magickdepict ${obdepict_srcs})
#  target_link_libraries(magickdepict ${OPENBABEL2_LIBRARIES})
#  install(TARGETS magickdepict DESTINATION bin)
  
# remove_definitions(-DUSE_MAGICK_PAINTER)
endif (MAGICK_CONFIG_EXE)

################################################################# LINUX USER #################################################################
#set(IMAGEMAGICK_LIBRARY "" CACHE STRING "where to find imagemagick library")
#set(IMAGEMAGICK_INCLUDE "" CACHE STRING "where to find imagemagick lincludes")

#include_directories(${IMAGEMAGICK_INCLUDE})
#target_link_libraries(mainFFT ${IMAGEMAGICK_LIBRARY})
#target_link_libraries(TestFFT ${IMAGEMAGICK_LIBRARY})

########################################
#  Adding executables
########################################

add_executable(testfft testfft.cpp
               ComplexNumber.cpp AbstractPadding.cpp ZeroPadding.cpp
           		PeriodizationPadding.cpp MirrorPadding.cpp Unpad.cpp ImageTools.cpp FFTPix.cpp)
           		
add_executable(testpad testpad.cpp
               ComplexNumber.cpp AbstractPadding.cpp ZeroPadding.cpp
           		PeriodizationPadding.cpp MirrorPadding.cpp Unpad.cpp ImageTools.cpp FFTPix.cpp)
           		
add_executable(testhisto testhisto.cpp
               ComplexNumber.cpp AbstractPadding.cpp ZeroPadding.cpp
           		PeriodizationPadding.cpp MirrorPadding.cpp Unpad.cpp ImageTools.cpp FFTPix.cpp)
           		
add_executable(main main.cpp
           ComplexNumber.cpp AbstractPadding.cpp ZeroPadding.cpp
           PeriodizationPadding.cpp MirrorPadding.cpp Unpad.cpp ImageTools.cpp FFTPix.cpp)          
               

add_executable(testfilter testfilter.cpp
				ComplexNumber.cpp AbstractPadding.cpp ZeroPadding.cpp
               PeriodizationPadding.cpp MirrorPadding.cpp Unpad.cpp ImageTools.cpp FFTPix.cpp)