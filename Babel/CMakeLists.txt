cmake_minimum_required(VERSION 2.8)

project(Babel)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(BabelAudioTest
	Babel/babel_common.h
	Babel/IAudioIO.hh
	Babel/ICompressor.hh
	Babel/OpusCompressor.cpp
	Babel/OpusCompressor.hh
	Babel/portaudio.h
	Babel/PortAudioIO.cpp
	Babel/PortAudioIO.hh
	Babel/AudioManager.hh
	Babel/AudioManager.cpp
	Babel/main.cpp)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MY_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MY_DIR})
SET(EXECUTABLE_OUTPUT_PATH ..)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/portaudio/includes ${PROJECT_SOURCE_DIR}/libs/opus/includes)

if(WIN32)
	find_package(Boost 1.55)
	#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
	LINK_DIRECTORIES(#${Boost_LIBRARY_DIRS}
					${PROJECT_SOURCE_DIR}/libs/portaudio/lib64 ${PROJECT_SOURCE_DIR}/libs/opus/lib64)
	target_link_libraries(BabelAudioTest ${PROJECT_SOURCE_DIR}/libs/portaudio/lib64/portaudio_x64.lib
					${PROJECT_SOURCE_DIR}/libs/opus/lib64/celt.lib
					${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_common.lib
					${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_fixed.lib
					${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_float.lib
					${PROJECT_SOURCE_DIR}/libs/opus/lib64/opus.lib
					)
					#${Boost_LIBRARIES}
else(WIN32)
#faire le linkage sur linux ici
#	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/portaudio)
	target_link_libraries(BabelAudioTest ${CMAKE_SOURCE_DIR}/libs/portaudio/libportaudio.a
					rt
					m
					asound
					jack
					pthread
					opus)
endif(WIN32)
