cmake_minimum_required(VERSION 2.8)
project(Babel)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(BabelAudioTest
	Babel/main.cpp
	Babel/babel_common.h
	Babel/PortAudioManager.hh
	Babel/PortAudioManager.cpp)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MY_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MY_DIR})
SET(EXECUTABLE_OUTPUT_PATH ..)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/portaudio/includes ${PROJECT_SOURCE_DIR}/libs/opus/includes)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/portaudio/lib64 ${PROJECT_SOURCE_DIR}/libs/opus/lib64)

if(WIN32)
	find_package(Boost 1.55)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
	target_link_libraries(BabelAudioTest ${Boost_LIBRARIES}
						${PROJECT_SOURCE_DIR}/libs/portaudio/lib64/portaudio_x64.lib
						${PROJECT_SOURCE_DIR}/libs/opus/lib64/celt.lib
						${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_common.lib
						${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_fixed.lib
						${PROJECT_SOURCE_DIR}/libs/opus/lib64/silk_float.lib
						${PROJECT_SOURCE_DIR}/libs/opus/lib64/opus.lib)
#else
#target_link_libraries(BabelAudioTest )
endif(WIN32)
