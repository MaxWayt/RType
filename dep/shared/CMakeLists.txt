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

file(GLOB_RECURSE source_files *.cpp *.h *.hpp *.hh)

set(shared_SRCS
    ${shared_SRCS}
    ${source_files}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(ALL_LIBS
    -lpthread
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(SHARED_LIBRARY_NAME "shared")

add_library(
    ${SHARED_LIBRARY_NAME}
    SHARED
    ${shared_SRCS}
)
target_link_libraries(${SHARED_LIBRARY_NAME} ${ALL_LIBS})

install(TARGETS ${SHARED_LIBRARY_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
