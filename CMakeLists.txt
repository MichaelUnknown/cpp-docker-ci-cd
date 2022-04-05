cmake_minimum_required(VERSION 3.14...3.22)


project(WebAPI LANGUAGES CXX)


# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info
include(cmake/CPM.cmake)


# Crow needs Boost 1.64 and does not provide CPM.cmake integration itself, so we have to get Boost first
find_package(Boost 1.64 QUIET)
if(NOT Boost_FOUND)
  # If not provided as system lib, use CPM.cmake to get Boost from the official repo
  message(STATUS "WebAPI: Boost system lib NOT found")
  CPMAddPackage(
    NAME Boost
    GITHUB_REPOSITORY boostorg/boost
    GIT_TAG boost-1.78.0
    VERSION 1.78.0
  )
  # Ugly workaround:
  # Boost cmake support is still experimental, the Boost::boost target is not provided if downloaded via
  # FetchContent_declare / CPM.cmake
  # Crow uses it for asio, so we fake the Boost:boost target as asio
  if(NOT TARGET Boost::boost)
    add_library(Boost::boost INTERFACE IMPORTED)
    target_link_libraries(Boost::boost INTERFACE Boost::asio)
  endif()
else()
  message(STATUS "WebAPI: Boost system lib found")
endif()
# add Crow
CPMAddPackage("gh:CrowCpp/Crow#v1.0+1@1.0.1")


# the app
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
