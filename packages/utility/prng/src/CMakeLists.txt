# Find all headers and sources (no updates to this file necessary!)
FILE(GLOB UTILITY_PRNG_HEADERS *.hpp)
FILE(GLOB UTILITY_PRNG_SOURCES *.cpp)

IF(CMAKE_VERBOSE_CONFIGURE)
  MESSAGE("UTILITY_PRNG_HEADERS = ${UTILITY_PRNG_HEADERS}")
  MESSAGE("UTILITY_PRNG_SOURCES = ${UTILITY_PRNG_SOURCES}")
ENDIF()

SET(SUBPACKAGE_LIB_NAME utility_prng)

# Create the utilitycore library
ADD_LIBRARY(${SUBPACKAGE_LIB_NAME} ${UTILITY_PRNG_SOURCES})
TARGET_LINK_LIBRARIES(${SUBPACKAGE_LIB_NAME} utility_core)
IF(${FACEMC_ENABLE_MPI})
  TARGET_LINK_LIBRARIES(${SUBPACKAGE_LIB_NAME} ${MPI_CXX_LIBRARIES})
ENDIF()

INSTALL(TARGETS ${SUBPACKAGE_LIB_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
INSTALL(FILES ${UTILITY_PRNG_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
