# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles/TicTacToe_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TicTacToe_autogen.dir/ParseCache.txt"
  "TicTacToe_autogen"
  )
endif()
