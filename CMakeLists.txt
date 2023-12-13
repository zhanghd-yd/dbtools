cmake_minimum_required(VERSION 3.10)

project(DBTools LANGUAGES CXX)

# zhd 启用C++17配置，cmake版本必须大于10
if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()# c++ 17

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")    
    add_definitions("/wd4251" "/wd4244") #关闭警告

    OPTION(USE_MP "use multiple" ON)
	OPTION(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP 
		"Set The Global Option COMPILE_FLAGS /MP to target." ON)
	if(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP OR USE_MP)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	endif()
	set(VS_STARTUP_PROJECT ${PROJECT_NAME})
endif ()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_DIR ${PROJECT_SOURCE_DIR}/../sdk/Qt/Qt5.12.8/msvc2017_64/)
set(CMAKE_PREFIX_PATH ${QT_DIR})
set(Qt5_MODULES
        Core
        Gui
        Widgets
        )
find_package(Qt5 COMPONENTS ${Qt5_MODULES} REQUIRED)
if (Qt5_FOUND)
    foreach (Qt5_MODULE ${Qt5_MODULES})
        include_directories(${Qt5${Qt5_MODULE}_INCLUDE_DIRS})
        link_libraries(Qt5::${Qt5_MODULE})
    endforeach ()
else ()
    message(WARNING "Qt5 Not Found!")
endif ()

message(STATUS "Copying Qt5 dlls")
file(GLOB QT_DLLS ${QT_DIR}/bin/*.dll)
file(COPY ${QT_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/)
message(STATUS "Copying Qt5 dlls - done")

######## #glog
set(GLOG_DIR ${PROJECT_SOURCE_DIR}/bin/glog/)
include_directories(${GLOG_DIR}/include/)
link_directories(${GLOG_DIR}/lib/)
add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)

message(STATUS "Copying glog dlls...")
file(GLOB GLOG_DLLS ${GLOG_DIR}/bin/*.dll)
file(COPY ${GLOG_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
message(STATUS "Copying glog -  done")

#######  jsoncpp
set(JSONCPP_DIR ${PROJECT_SOURCE_DIR}/bin/jsoncpp/)
include_directories(${JSONCPP_DIR}/include/)
link_directories(${JSONCPP_DIR}/lib/)

######  #mariadb
set(MARIADB_DIR ${PROJECT_SOURCE_DIR}/bin/mariadb)
link_directories(${MARIADB_DIR})
message(STATUS "Copying mariadb dlls...")
file(GLOB MARIADB_DLLS ${MARIADB_DIR}/*.dll)
file(COPY ${MARIADB_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
message(STATUS "Copying mariadb -  done")

#fmt
set(FMT_DIR ${PROJECT_SOURCE_DIR}/bin/fmt)
link_directories(${FMT_DIR})

link_libraries(
    debug fmtd optimized fmt
    debug libmariadb optimized libmariadb
    debug jsoncppd optimized jsoncpp
    debug glogd optimized glog
)

## rttr
set(RTTR_DIR ${PROJECT_SOURCE_DIR}/bin/rttr)
include_directories(${RTTR_DIR}/include)
link_directories(${RTTR_DIR}/lib)
add_definitions(-DRTTR_DLL)
add_definitions(-DQT_NO_FLOAT16_OPERATORS)
include_directories(${PROJECT_SOURCE_DIR}/bin/rapidjson-1.1.0/)
link_libraries(
	debug rttr_core_d optimized rttr_core
)
message(STATUS "Copying rttr dlls...")
file(GLOB RTTR_DLLS ${RTTR_DIR}/bin/*.dll)
file(COPY ${RTTR_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
message(STATUS "Copying rttr -  done")
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
aux_source_directory(./src/DBBaseAutoGen BASE_SRC_LIST)
aux_source_directory(./src/DBDataAutoGen DATA_SRC_LIST)
aux_source_directory(./src/base BASE_SRC_LIST)
aux_source_directory(./src/rttr_serialization RTTR_SRC_LIST)

file(GLOB INCLUDE_LIST "*.h" ".hpp")

add_executable(${PROJECT_NAME} main.cpp ${BASE_SRC_LIST} ${DATA_SRC_LIST} ${BASE_SRC_LIST} ${RTTR_SRC_LIST} ${INCLUDE_LIST})