Find_Package(SFML REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

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

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++0x")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -std=c++0x")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -std=c++0x")

file(GLOB_RECURSE source_files *.cpp *.h *.hpp *.hh)
file(GLOB_RECURSE source_core Core/*.cpp Core/*.h Core/*.hpp Core/*.hh)

set(damncute_SRCS
    ${damncute_SRCS}
    ${source_files}
    ${source_core}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_SOURCE_DIR}/dep
    ${SFML_INCLUDE_DIR}
)

set(ALL_LIBS
    ${SFML_LIBRARIES}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(DAMNCUTE_LIBRARY_NAME "damncute")

add_library(
    ${DAMNCUTE_LIBRARY_NAME}
    SHARED
    ${damncute_SRCS}
)