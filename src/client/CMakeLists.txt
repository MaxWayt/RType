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
file(GLOB_RECURSE source_actions Actions/*.cpp Actions/*.h Actions/*.hpp Actions/*.hh)

set(rtype_client_SRCS
    ${rtype_client_SRCS}
    ${source_files}
    ${source_actions}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Actions
    ${CMAKE_SOURCE_DIR}/dep
    ${CMAKE_SOURCE_DIR}/dep/damncute
    ${SFML_INCLUDE_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(ALL_LIBS
    ${SFML_LIBRARY}
    -ldamncute
)

set(CLIENT_EXECUTABLE_NAME "rtype-client")

add_executable(${CLIENT_EXECUTABLE_NAME}
    ${rtype_client_SRCS}
)
target_link_libraries(${CLIENT_EXECUTABLE_NAME} ${ALL_LIBS})

install(TARGETS ${CLIENT_EXECUTABLE_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
install(FILES ${CLIENT_EXECUTABLE_NAME}.conf.dist DESTINATION "${CMAKE_INSTALL_PREFIX}/etc")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/resources DESTINATION "${CMAKE_INSTALL_PREFIX}")
