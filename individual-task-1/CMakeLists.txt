file(GLOB_RECURSE SOURCE_FILES src/*.c)
file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE TEST_FILES test/*.cpp)

add_library(it-1 ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(it-1
        PUBLIC    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        INTERFACE $<INSTALL_INTERFACE:include>)


enable_testing()
add_executable(it-1-test ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES})
target_include_directories(it-1-test
        PUBLIC    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(it-1-test gtest_main)