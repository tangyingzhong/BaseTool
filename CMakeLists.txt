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
add_definitions(-DEXPORT_CLASS)

# 设置不同编译方式下的优化方式
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -o0")
elseif(${BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -o3")
endif()

project(BaseTool)

# ShareLib's path
if(WINDOWS)
    set(ShareLibPath ${CMAKE_CURRENT_SOURCE_DIR}/ShareLib/Win)
elseif(MACOS)
    set(ShareLibPath ${CMAKE_CURRENT_SOURCE_DIR}/ShareLib/Mac)
elseif(LINUX)
    set(ShareLibPath ${CMAKE_CURRENT_SOURCE_DIR}/ShareLib/Linux)
else()
    set(ShareLibPath ${CMAKE_CURRENT_SOURCE_DIR}/ShareLib/Win)
endif()
message(STATUS "ShareLib=" ${ShareLibPath})

# Include the head files
include(${PROJECT_SOURCE_DIR})

# Link poco library
if(WINDOWS)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(PocoLibs PocoCryptod.dll
            PocoDatad.dll
            PocoSqlited.dll
            PocoEncodingsd.dll
            PocoFoundationd.dll
            PocoJSONd.dll
            PocoNetd.dll
            PocoNetSSLd.dll
            PocoUtild.dll
            PocoXMLd.dll
            PocoZipd.dll)
    else()
        set(PocoLibs PocoCrypto.dll
            PocoData.dll
            PocoSqlite.dll
            PocoEncodings.dll
            PocoFoundation.dll
            PocoJSON.dll
            PocoNet.dll
            PocoNetSSL.dll
            PocoUtil.dll
            PocoXML.dll
            PocoZip.dll)
    endif()
elseif(MACOS)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(PocoLibs libPocoCryptod.dylib
            libPocoDatad.dylib
            libPocoSqlited.dylib
            libPocoEncodingsd.dylib
            libPocoFoundationd.dylib
            libPocoJSONd.dylib
            libPocoNetd.dylib
            libPocoNetSSLd.dylib
            libPocoUtild.dylib
            libPocoXMLd.dylib
            libPocoZipd.dylib)
    else()
        set(PocoLibs libPocoCrypto.dylib
            libPocoData.dylib
            libPocoSqlite.dylib
            libPocoEncodings.dylib
            libPocoFoundation.dylib
            libPocoJSON.dylib
            libPocoNet.dylib
            libPocoNetSSL.dylib
            libPocoUtil.dylib
            libPocoXML.dylib
            libPocoZip.dylib)
    endif()
elseif(LINUX)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(PocoLibs libPocoCryptod.so
            libPocoDatad.so
            libPocoSqlited.so
            libPocoEncodingsd.so
            libPocoFoundationd.so
            libPocoJSONd.so
            libPocoNetd.so
            libPocoNetSSLd.so
            libPocoUtild.so
            libPocoXMLd.so
            libPocoZipd.so)
    else()
        set(PocoLibs libPocoCrypto.so
            libPocoData.so
            libPocoSqlite.so
            libPocoEncodings.so
            libPocoFoundation.so
            libPocoJSON.so
            libPocoNet.so
            libPocoNetSSL.so
            libPocoUtil.so
            libPocoXML.so
            libPocoZip.so)
    endif()
else()
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(PocoLibs PocoCryptod.dll
            PocoDatad.dll
            PocoSqlited.dll
            PocoEncodingsd.dll
            PocoFoundationd.dll
            PocoJSONd.dll
            PocoNetd.dll
            PocoNetSSLd.dll
            PocoUtild.dll
            PocoXMLd.dll
            PocoZipd.dll)
    else()
        set(PocoLibs PocoCrypto.dll
            PocoData.dll
            PocoSqlite.dll
            PocoEncodings.dll
            PocoFoundation.dll
            PocoJSON.dll
            PocoNet.dll
            PocoNetSSL.dll
            PocoUtil.dll
            PocoXML.dll
            PocoZip.dll)
    endif()
endif()

if(WINDOWS)
    link_directories(${ShareLibPath}/Poco/lib/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})
elseif(MACOS)
    link_directories(${ShareLibPath}/Poco/lib/${CMAKE_BUILD_TYPE})
elseif(LINUX)
    link_directories(${ShareLibPath}/Poco/lib/${CMAKE_BUILD_TYPE})
else()
    link_directories(${ShareLibPath}/Poco/lib/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})
endif()
link_libraries(${PocoLibs})

# Source group 
set(AudioPlayerSrc Tool/AudioPlayer/AudioPlayer.h
    Tool/AudioPlayer/AudioPlayer.cpp)
set(BufferSrc Tool/Buffer/Buffer.h)
set(CommonSrc Tool/Common/Common.h
    Tool/Common/Common.cpp)
set(ConfigSrc Tool/Config/BTConfig.h)
set(CryptoSrc Tool/Crypto/BTCrypto.h
    Tool/Crypto/BTCrypto.cpp)
set(DateTimeSrc Tool/DateTime/DateTime.h
    Tool/DateTime/DateTime.cpp)
set(DirectorySrc Tool/Directory/Directory.h
    Tool/Directory/Directory.cpp)
set(DllLoaderSrc Tool/DllLoader/DllLoader.h
    Tool/DllLoader/DllLoader.cpp)
set(EncodingSrc Tool/Encoding/Encoding.h
    Tool/Encoding/Encoding.cpp)
set(FileSrc Tool/File/File.h
    Tool/File/File.cpp)
set(GuidSrc Tool/GUID/Guid.h
    Tool/GUID/Guid.cpp)
set(HttpClientSrc Tool/HttpClient/HttpClient.h
    Tool/HttpClient/HttpClient.cpp)
set(HttpServerSrc Tool/HttpServer/HttpServer.h
    Tool/HttpServer/HttpServer.cpp)
set(IniSrc Tool/Ini/Ini.h
    Tool/Ini/Ini.cpp)
set(JsonSrc Tool/Json/Json.h
    Tool/Json/Json.cpp)
set(LoggerSrc Tool/Logger/Logger.h
    Tool/Logger/Logger.cpp)
set(SqliteSrc Tool/Sqlite/Sqlite.h
    Tool/Sqlite/Sqlite.cpp)
set(StopWatchSrc Tool/StopWatch/StopWatch.h
    Tool/StopWatch/StopWatch.cpp)
set(StringSrc Tool/String/String.h
    Tool/String/String.cpp)
set(TarSrc Tool/Tar/Tar.h
    Tool/Tar/Tar.cpp)
set(TCPClientSrc Tool/TCPClient/TCPClient.h
    Tool/TCPClient/TCPClient.cpp)
set(TCPServerSrc Tool/TCPServer/TCPServer.h
    Tool/TCPServer/TCPServer.cpp)
set(ThreadPoolSrc Tool/ThreadPool/ThreadPool.h
    Tool/ThreadPool/ThreadPool.cpp)
set(TimerSrc Tool/Timer/Timer.h
    Tool/Timer/Timer.cpp)
set(UDPClientSrc Tool/UDPClient/UDPClient.h
    Tool/UDPClient/UDPClient.cpp)
set(UDPServerSrc Tool/UDPServer/UDPServer.h
    Tool/UDPServer/UDPServer.cpp)
set(WSClientSrc Tool/WSClient/WSClient.h
    Tool/WSClient/WSClient.cpp)
set(WSServerSrc Tool/WSServer/WSServer.h
    Tool/WSServer/WSServer.cpp)
set(XMLSrc Tool/XML/XML.h
    Tool/XML/XML.cpp)
set(ZipSrc Tool/Zip/BTZip.h
    Tool/Zip/BTZip.cpp)

source_group(AudioPlayer ${AudioPlayerSrc})
source_group(Buffer ${BufferSrc})
source_group(Common ${CommonSrc})
source_group(Config ${ConfigSrc})
source_group(Crypto ${CryptoSrc})
source_group(DateTime ${DateTimeSrc})
source_group(Directory ${DirectorySrc})
source_group(DllLoader ${DllLoaderSrc})
source_group(Encoding ${EncodingSrc})
source_group(File ${FileSrc})
source_group(GUID ${GuidSrc})
source_group(HttpClient ${HttpClientSrc})
source_group(HttpServer ${HttpServerSrc})
source_group(Ini ${IniSrc})
source_group(Json ${JsonSrc})
source_group(Logger ${LoggerSrc})
source_group(Sqlite ${SqliteSrc})
source_group(StopWatch ${StopWatchSrc})
source_group(String ${StringSrc})
source_group(Tar ${TarSrc})
source_group(TCPClient ${TCPClientSrc})
source_group(TCPServer ${TCPServerSrc})
source_group(ThreadPool ${ThreadPoolSrc})
source_group(Timer ${TimerSrc})
source_group(UDPClient ${UDPClientSrc})
source_group(UDPServer ${UDPServerSrc})
source_group(WSClient ${WSClientSrc})
source_group(WSServer ${WSServerSrc})
source_group(XML ${XMLSrc})
source_group(Zip ${ZipSrc})

# Set the library output path
if(WINDOWS)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})
else()
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE})
endif()

# Output library
add_library(BaseTool ${AudioPlayerSrc}
    ${BufferSrc}
    ${CommonSrc}
    ${ConfigSrc}
    ${CryptoSrc}
    ${DateTimeSrc}
    ${DirectorySrc}
    ${DllLoaderSrc}
    ${EncodingSrc}
    ${FileSrc}
    ${GuidSrc}
    ${HttpClientSrc}
    ${HttpServerSrc}
    ${IniSrc}
    ${JsonSrc}
    ${LoggerSrc}
    ${SqliteSrc}
    ${StopWatchSrc}
    ${StringSrc}
    ${TarSrc}
    ${TCPClientSrc}
    ${TCPServerSrc}
    ${ThreadPoolSrc}
    ${TimerSrc}
    ${UDPClientSrc}
    ${UDPServerSrc}
    ${WSClientSrc}
    ${WSServerSrc}
    ${XMLSrc}
    ${ZipSrc}
)
