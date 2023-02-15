cmake_minimum_required(VERSION 3.16)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
endif()

project(pyminr LANGUAGES C)

include(FetchContent)

set(CMAKE_C_VISIBILITY_PRESET hidden)

# Fetch Minr repo
FetchContent_Declare(
        minr
        GIT_REPOSITORY https://github.com/scanoss/minr.git
        GIT_TAG        2.5.7
)
FetchContent_Populate(minr)


add_library(minr SHARED)

target_sources(minr PRIVATE src/crypto.c)
target_include_directories(minr
  PRIVATE  
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${minr_SOURCE_DIR}/inc  
)

if(WIN32)
  target_sources(minr PRIVATE src/asprintf.c)
  target_include_directories(minr
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/win        
  )  
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    target_link_libraries(minr PRIVATE -dead_strip)
    target_link_libraries(minr PRIVATE -Wl,-x)
endif()

install(TARGETS minr
  RUNTIME DESTINATION lib/
  LIBRARY DESTINATION lib/
  )