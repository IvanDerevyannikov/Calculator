# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Calculator\\CMakeFiles\\Calculator_autogen.dir\\AutogenUsed.txt"
  "Calculator\\CMakeFiles\\Calculator_autogen.dir\\ParseCache.txt"
  "Calculator\\Calculator_autogen"
  )
endif()
