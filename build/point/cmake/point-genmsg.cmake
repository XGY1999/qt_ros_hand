# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "point: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipoint:/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(point_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_custom_target(_point_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "point" "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(point
  "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/point
)

### Generating Services

### Generating Module File
_generate_module_cpp(point
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/point
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(point_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(point_generate_messages point_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_dependencies(point_generate_messages_cpp _point_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(point_gencpp)
add_dependencies(point_gencpp point_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS point_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(point
  "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/point
)

### Generating Services

### Generating Module File
_generate_module_eus(point
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/point
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(point_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(point_generate_messages point_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_dependencies(point_generate_messages_eus _point_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(point_geneus)
add_dependencies(point_geneus point_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS point_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(point
  "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/point
)

### Generating Services

### Generating Module File
_generate_module_lisp(point
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/point
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(point_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(point_generate_messages point_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_dependencies(point_generate_messages_lisp _point_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(point_genlisp)
add_dependencies(point_genlisp point_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS point_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(point
  "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/point
)

### Generating Services

### Generating Module File
_generate_module_nodejs(point
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/point
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(point_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(point_generate_messages point_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_dependencies(point_generate_messages_nodejs _point_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(point_gennodejs)
add_dependencies(point_gennodejs point_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS point_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(point
  "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/point
)

### Generating Services

### Generating Module File
_generate_module_py(point
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/point
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(point_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(point_generate_messages point_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xgy/ws_xgy/ws_project/qt_ros_hand/src/point/msg/point.msg" NAME_WE)
add_dependencies(point_generate_messages_py _point_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(point_genpy)
add_dependencies(point_genpy point_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS point_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/point)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/point
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(point_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/point)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/point
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(point_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/point)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/point
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(point_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/point)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/point
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(point_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/point)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/point\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/point
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(point_generate_messages_py std_msgs_generate_messages_py)
endif()
