cmake_minimum_required(VERSION 3.7)

project(Zeiterfassung C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CJSON_VERSION_SO 1)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(CURL REQUIRED)
find_package(JSON-C REQUIRED)
find_package(json-c CONFIG)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2_TTF_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${JSON-C_INCLUDE_DIRS})
include_directories(${json-c_DIRS})



add_executable(Zeiterfassung src/gui.c)
target_link_libraries(Zeiterfassung PRIVATE json-c::json-c ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${CURL_LIBRARIES} ${JSON-C_LIBRARIES} )
