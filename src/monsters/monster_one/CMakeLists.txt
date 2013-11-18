Find_Package(SFML REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} -std=c++0x")

if ( APPLE )
    set(CMAKE_CXX_FLAGS "-D OSX -D UNIX -stdlib=libc++ ${CMAKE_CXX_FLAGS}")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
elseif ( UNIX )
    set(CMAKE_CXX_FLAGS "-D LINUX -D UNIX ${CMAKE_CXX_FLAGS}")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lpthread")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lpthread")
elseif ( WIN32 )

endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DEBUG_FLAGS} -std=c++0x")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${DEBUG_FLAGS} -std=c++0x")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${DEBUG_FLAGS} -std=c++0x")

file(GLOB_RECURSE source_file *.cpp *.h *.hpp *.hh)

set(monsters_SRCS
    ${monsters_SRCS}
    ${source_file}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/dep/damncute
    ${CMAKE_SOURCE_DIR}/dep
    ${SFML_INCLUDE_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(ALL_LIBS
    ${SFML_LIBRARY}
    -ldamncute
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(ZIZI_LIBRARY_NAME "zizi")

add_library(
    ${ZIZI_LIBRARY_NAME}
    SHARED
    ${monsters_SRCS}
)
target_link_libraries(${ZIZI_LIBRARY_NAME} ${ALL_LIBS})

install(TARGETS ${ZIZI_LIBRARY_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
