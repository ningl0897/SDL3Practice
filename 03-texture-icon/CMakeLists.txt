cmake_minimum_required(VERSION 3.16)
project(demo C)

# ON=用系统装的 SDL3，OFF=用源码编译
option(USE_SYSTEM_SDL "Use system SDL3" ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/SDL3-3.4.16")
endif()

if(USE_SYSTEM_SDL)
  find_package(SDL3 REQUIRED)
  find_package(SDL3_image REQUIRED)
else()
  set(SDL_TESTS    OFF CACHE BOOL "" FORCE)
  set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(SDL_INSTALL  OFF CACHE BOOL "" FORCE)
  add_subdirectory(../SDL SDL)
  add_subdirectory(../SDL3_image SDL3_image)
endif()

add_executable(demo WIN32 src/main.c)
target_link_libraries(demo PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

if(WIN32)
  add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:SDL3::SDL3>
      $<TARGET_FILE:SDL3_image::SDL3_image>
      $<TARGET_FILE_DIR:demo>)
endif()
