
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

file(GLOB_RECURSE source_files *.cpp *.h *.hpp)
file(GLOB_RECURSE source_game game/*.cpp game/*.h game/*.hpp)
file(GLOB_RECURSE source_utils utils/*.cpp utils/*.h utils/*.hpp)
file(GLOB_RECURSE source_config config/*.cpp config/*.h config/*.hpp)

set(rtype_server_SRCS
    ${rtype_server_SRCS}
    ${source_files}
    ${source_utils}
    ${source_game}
    ${source_config}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_SOURCE_DIR}/dep/shared
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(ALL_LIBS
    shared
)

set(SERVER_NAME "rtype-server")
set(SERVER_EXECUTABLE_NAME ${SERVER_NAME}-bin)

add_executable(${SERVER_EXECUTABLE_NAME}
    ${rtype_server_SRCS}
)

target_link_libraries(${SERVER_EXECUTABLE_NAME} ${ALL_LIBS})
if ( WIN32 )
	target_link_libraries(${SHARED_LIBRARY_NAME} ws2_32)
endif()

install_targets(/bin ${SERVER_EXECUTABLE_NAME})
install_programs(/bin ${SERVER_NAME})
install_files(/etc ${SERVER_NAME}.conf.dist)
