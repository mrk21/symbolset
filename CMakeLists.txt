cmake_minimum_required(VERSION 2.8)
project(symbolset)

set(COMPILER_NOT_SUPPORT_MESSAGE "This compiler is not supported! (Supported compiler is GCC 4.8 later or Clang 3.3 later)")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION LESS "4.8")
    message(FATAL_ERROR ${COMPILER_NOT_SUPPORT_MESSAGE})
  endif()
  
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -Wextra")
  
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION LESS "3.3")
    message(FATAL_ERROR ${COMPILER_NOT_SUPPORT_MESSAGE})
  endif()
  
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -stdlib=libc++ -Wall -Wextra")
  
else()
  message(FATAL_ERROR ${COMPILER_NOT_SUPPORT_MESSAGE})
endif()

find_package(Boost)
include_directories(${PROJECT_SOURCE_DIR})

if(IS_EXAMPLES)
  add_subdirectory(examples)
else()
  add_subdirectory(test)
endif()
