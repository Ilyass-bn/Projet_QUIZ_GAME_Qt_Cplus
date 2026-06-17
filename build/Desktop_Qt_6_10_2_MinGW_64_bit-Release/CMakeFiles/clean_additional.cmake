# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Projet_quiz_game_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Projet_quiz_game_autogen.dir\\ParseCache.txt"
  "Projet_quiz_game_autogen"
  )
endif()
