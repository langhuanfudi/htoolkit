cmake_minimum_required(VERSION 3.20)
project(htoolkit)

#加载自定义模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

#设置库文件路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#设置可执行程序路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#设置子目录
set(SUB_DIR_LIST thread util)

#安装目录
if (WIN32)
    set(INSTALL_PATH_LIB $ENV{HOME}/${PROJECT_NAME}/lib)
    set(INSTALL_PATH_INCLUDE $ENV{HOME}/${PROJECT_NAME}/include)
else ()
    set(INSTALL_PATH_LIB lib)
    set(INSTALL_PATH_INCLUDE include)
endif ()

foreach (SUB_DIR ${SUB_DIR_LIST})
    #    遍历源文件
    aux_source_directory(src/${SUB_DIR} SRC_LIST)
    #    安装头文件至系统目录
    install(DIRECTORY src/${SUB_DIR} DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")
endforeach ()

#非苹果平台移除.mm文件
if (NOT APPLE)
    list(REMOVE_ITEM SRC_LIST "src/Network/Socket_ios.mm")
endif ()

if (WIN32)
    set(LINK_LIB_LIST WS2_32 Iphlpapi shlwapi)
else ()
    set(LINK_LIB_LIST)
endif ()

#查找openssl是否安装
#查找mysql是否安装

#打印库文件
message(STATUS "将链接依赖库: ${LINK_LIB_LIST}")
#-std=c++20
set(CMAKE_CXX_STANDARD 20)

if (NOT WIN32)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-predefined-identifier-outside-function)
endif ()

#编译动态库
if (NOT IOS AND NOT ANDROID AND NOT WIN32)
    add_library(${PROJECT_NAME}_shared SHARED ${SRC_LIST})
    target_include_directories(${PROJECT_NAME}_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(${PROJECT_NAME}_shared ${LINK_LIB_LIST})
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
    install(TARGETS ${PROJECT_NAME}_shared ARCHIVE DESTINATION ${INSTALL_PATH_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB})
endif ()

#编译静态库
add_library(${PROJECT_NAME}_static STATIC ${SRC_LIST})

#引用头文件路径
target_include_directories(${PROJECT_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

#安装静态库至系统目录
install(TARGETS ${PROJECT_NAME}_static ARCHIVE DESTINATION ${INSTALL_PATH_LIB})

#测试程序
#if (NOT IOS)
#    add_subdirectory(tests)
#endif ()
