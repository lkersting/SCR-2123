# Find all headers and sources (no updates to this file necessary!)
FILE(GLOB DATA_GEN_XSDIR_HEADERS *.hpp)
FILE(GLOB DATA_GEN_XSDIR_SOURCES *.cpp)

IF(CMAKE_VERBOSE_CONFIGURE)
  MESSAGE("DATA_GEN_XSDIR_HEADERS = ${DATA_GEN_XSDIR_HEADERS}")
  MESSAGE("DATA_GEN_XSDIR_SOURCES = ${DATA_GEN_XSDIR_SOURCES}")
ENDIF()

SET(SUBPACKAGE_LIB_NAME data_gen_xsdir)

# Create the subpackage library
ADD_LIBRARY(${SUBPACKAGE_LIB_NAME} ${DATA_GEN_XSDIR_SOURCES})
TARGET_LINK_LIBRARIES(${SUBPACKAGE_LIB_NAME} monte_carlo_collision_native)

INSTALL(TARGETS ${SUBPACKAGE_LIB_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
INSTALL(FILES ${DATA_GEN_XSDIR_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)