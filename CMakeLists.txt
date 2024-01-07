cmake_minimum_required(VERSION 3.5.0)

# 获取当前所在平台
if(CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# 强制使用C++11标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11) 

# 指定需要的最低MacOS版本
if(MACOS)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "支持的最低MacOS版本" FORCE)
endif()

# Windows项目添加Unicode支持，避免中文乱码
if(WINDOWS)
    add_definitions("-DUNICODE" "-D_UNICODE")
endif()

# 设置不同编译方式下的优化方式
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -o0")
elseif(${BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -o3")
endif()

project(BaseTool)

# ShareLib's path
set(ShareLibPath ${CMAKE_CURRENT_SOURCE_DIR}/../ShareLib)

