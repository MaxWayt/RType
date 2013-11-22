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

file(GLOB_RECURSE source_file ../../client/*.cpp ../../client/*.h ../../client/*.hpp ../../client/*.hh)
file(GLOB_RECURSE source_actions ../../client/Actions/*.cpp ../../client/Actions/*.h ../../client/Actions/*.hpp ../../client/Actions/*.hh)
file(GLOB_RECURSE source_game ../../client/game/*.cpp ../../client/game/*.h ../../client/game/*.hpp ../../client/game/*.hh)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

file(GLOB_RECURSE source_monster_test *.cpp *.h *.hh *.hpp)
set(monster_test_SRCS
    ${monster_test_SRCS}
    ${source_file}
    ${source_actions}
    ${source_game}
    ${source_monster_test}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/dep
    ${CMAKE_SOURCE_DIR}/dep/damncute
    ${CMAKE_SOURCE_DIR}/dep/shared
    ${CMAKE_SOURCE_DIR}/src/client/
    ${CMAKE_SOURCE_DIR}/src/client/Actions
    ${CMAKE_SOURCE_DIR}/src/client/game
    ${SFML_INCLUDE_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

set(ALL_LIBS
    ${SFML_LIBRARY}
    -ldamncute
    -lshared
    -ldl
)

set(MONSTER_TEST_LIBRARY_NAME "boss1")
add_library(${MONSTER_TEST_LIBRARY_NAME}
    SHARED
    ${monster_test_SRCS}
)
target_link_libraries(${MONSTER_TEST_LIBRARY_NAME} ${ALL_LIBS})

install(TARGETS ${MONSTER_TEST_LIBRARY_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
