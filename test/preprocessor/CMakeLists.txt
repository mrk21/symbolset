set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-pp-token -E -P -x c++")

get_property(INCLUDES DIRECTORY PROPERTY INCLUDE_DIRECTORIES)

add_custom_target("pp_test"
  COMMAND ruby test.rb "${CMAKE_CXX_COMPILER}" "${CMAKE_CXX_FLAGS}" "${INCLUDES}"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test/preprocessor
)
