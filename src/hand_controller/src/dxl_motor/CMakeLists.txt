# 需要cmake的最低版本
cmake_minimum_required(VERSION 3.15)

# 设置目标名称
set( TARGET_NAME "dxl_motor" )


# 把.cpp和.c文件都塞到SOURCE_FILES里
file(GLOB SOURCE_FILES "*.cpp" "*.c" )
# 把.cpp和.c文件都塞到HEADER_FILES里
file(GLOB HEADER_FILES "*.h"  "*.hpp" )

# 把interface里的*.h文件都塞到INTERFACE_FILES里
file(GLOB INTERFACE_FILES 
    ${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}/*.h 
    ${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}/*.hpp 
    )

# 把 INTERFACE_FILES 中的文件归类到 InterfaceHeaders 下，可以清楚的梳理目录结构
source_group( InterfaceHeaders FILES ${INTERFACE_FILES} )

# 把${SOURCE_FILES} ${HEADER_FILES} ${INTERFACE_FILES}等包装成一个静态库
add_library( ${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${INTERFACE_FILES} )
add_library( ${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME} )

# 添加头文件路径
target_include_directories( ${TARGET_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    #     ${PROJECT_BINARY_DIR}/include
    #     $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${PROJECT_SOURCE_DIR}/depends_win/serviceinterface/include/serviceinterface>
    #     $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${PROJECT_SOURCE_DIR}/depends_win/pthread/include>
    # PRIVATE
        
        # $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:${PROJECT_SOURCE_DIR}/depends_linux/robotSDK/inc>
    )

# 链接其他的库
target_link_libraries( ${TARGET_NAME} 
#     PUBLIC
#         # ${Boost_LIBRARIES}
#         Boost::headers
#         $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${PROJECT_SOURCE_DIR}/depends_win/serviceinterface/lib/serviceinterface2.lib>
# #        ${PROJECT_SOURCE_DIR}/depends_win/serviceinterface/lib/serviceinterface2.lib
#         $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${PROJECT_SOURCE_DIR}/depends_win/pthread/lib/x64/pthreadVC2.lib>
    PRIVATE 
        dynamixel_lib
        # $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:${PROJECT_SOURCE_DIR}/depends_linux/log4cplus/linux_x64/lib/liblog4cplus-1.2.so.5.1.4>
        # $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:${PROJECT_SOURCE_DIR}/depends_linux/robotSDK/lib/linux_x64/libauborobotcontroller.so.1.3.2>
    # INTERFACE
    #     $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Linux>:pthread>
        )

# target_compile_definitions( ${TARGET_NAME} 
#     PUBLIC
#         _USE_MATH_DEFINES

# )



