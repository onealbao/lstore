cmake_minimum_required (VERSION 2.6)

project(lstore-mongodb C)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# These variables get compiled into the final module.
set(MONGODBL_VERSION_MAJOR 0)
set(MONGODBL_VERSION_MINOR 1)
#include (Timestamp)
#TIMESTAMP(MONGODBL_TIMESTAMP)

set(MONGODBL_OBJS
        src/mongodb_lstore.c
    )
set(MONGODBL_LIBS
	mongo::mongoc_shared
        toolbox
        gop
        ibp
        lio
        ${APR_LIBRARY}
        ${APRUTIL_LIBRARY}
    )
set(MONGODBL_INC
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/toolbox
        ${CMAKE_SOURCE_DIR}/src/gop
        ${CMAKE_SOURCE_DIR}/src/ibp
        ${CMAKE_SOURCE_DIR}/src/lio
        ${APR_INCLUDE_DIR}
        ${APRUTIL_INCLUDE_DIR}
        ${TCMU_INCLUDE_DIR}
    )

# Share object files
add_library(mongodbl-objs OBJECT ${MONGODBL_OBJS})
set_target_properties(mongodbl-objs PROPERTIES POSITION_INDEPENDENT_CODE ON)
include_directories(mongodbl-objs PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/toolbox
        ${CMAKE_SOURCE_DIR}/src/gop
        ${CMAKE_SOURCE_DIR}/src/ibp
        ${CMAKE_SOURCE_DIR}/src/lio
        ${APR_INCLUDE_DIR}
        ${APRUTIL_INCLUDE_DIR}
        ${TCMU_INCLUDE_DIR}
)

add_library(mongodb_lstore SHARED $<TARGET_OBJECTS:mongodbl-objs>)
set_target_properties(
  mongodb_lstore
  PROPERTIES
  LINKER_LANGUAGE C
  PREFIX    ""
  VERSION   "${MONGODBL_VERSION_MAJOR}.${MONGODBL_VERSION_MINOR}.1"
  SOVERSION "0"
  OUTPUT_NAME "mongodb_lstore"
)

target_link_libraries(mongodb_lstore ${MONGODBL_LIBS})

# SHUNXING
message ("--SHUNXING \"${MONGODBL_INC}\"")

# The "hello_mongoc.c" sample program is shared among four tests.
add_executable(hello_mongoc src/hello_mongoc.c)
set_target_properties(hello_mongoc PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (hello_mongoc mongodb_lstore ${MONGODBL_LIBS})

if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR "lib64")
endif()

install(
  TARGETS mongodb_lstore
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)






