cmake_minimum_required(VERSION 3.14...3.22)


project(WebAPI LANGUAGES CXX)


# add dependencies via CPM.cmake
include(cmake/CPM.cmake)

# add Crow with boost
CPMAddPackage(
  NAME Crow
  GITHUB_REPOSITORY CrowCpp/Crow
  VERSION 1.3.4
  OPTIONS
    "CROW_USE_BOOST ON"
)

# the app
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
