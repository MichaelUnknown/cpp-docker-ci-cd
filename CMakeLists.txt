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
    GIT_TAG boost-1.81.0
    VERSION 1.81.0
  )

  # Ugly workaround:
  # Boost cmake support is still experimental, the Boost::headers / Boost::boost target
  # is not provided if downloaded via FetchContent_declare / CPM.cmake
  # so we add it manually

  if(NOT TARGET Boost::headers)
    message(STATUS "manually adding Boost::headers")

    set(__boost_libs_dir "${Boost_SOURCE_DIR}/libs/")
    file(GLOB __boost_all_components
      LIST_DIRECTORIES true
      RELATIVE "${__boost_libs_dir}"
      "${__boost_libs_dir}/*/include")
    file(GLOB __boost_all_components_num
      LIST_DIRECTORIES true
      RELATIVE "${__boost_libs_dir}"
      "${__boost_libs_dir}/numeric/*/include")

    foreach(__dir ${__boost_all_components})
      set(__full_dir "${__boost_libs_dir}${__dir}")
      #message(STATUS "full dir: ${__full_dir}")
      list(APPEND __boost_all_includes ${__full_dir})
    endforeach()
    foreach(__dir ${__boost_all_components_num})
      set(__full_dir "${__boost_libs_dir}${__dir}")
      #message(STATUS "full num dir: ${__full_dir}")
      list(APPEND __boost_all_includes ${__full_dir})
    endforeach()

    list(LENGTH __boost_all_includes __boost_all_includes_count)
    message(STATUS "number of include dirs discovered: ${__boost_all_includes_count}")

    # add target
    add_library(Boost::headers INTERFACE IMPORTED)
    set_target_properties(Boost::headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__boost_all_includes}")
    #get_target_property(xxx Boost::headers INTERFACE_INCLUDE_DIRECTORIES)
    #foreach(xx ${xxx})
    #  message(STATUS "Boost::headers includes: ${xx}")
    #endforeach()
  endif()

  if(NOT TARGET Boost::boost)
    message(STATUS "manually adding Boost::boost")
    add_library(Boost::boost INTERFACE IMPORTED)
    target_link_libraries(Boost::boost INTERFACE Boost::headers)
  endif()
else()
  message(STATUS "WebAPI: Boost system lib found")
endif()

# add Crow
CPMAddPackage(
  NAME Crow
  GITHUB_REPOSITORY CrowCpp/Crow
  GIT_TAG v1.0+1
  VERSION 1.0.1
  OPTIONS
    "CROW_INSTALL OFF"
)

# the app
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
