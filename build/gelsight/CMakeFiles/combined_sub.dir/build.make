# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/xgy/Downloads/cmake-3.22.4-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/xgy/Downloads/cmake-3.22.4-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xgy/ws_xgy/ws_project/qt_ros_hand/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xgy/ws_xgy/ws_project/qt_ros_hand/build

# Include any dependencies generated for this target.
include gelsight/CMakeFiles/combined_sub.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include gelsight/CMakeFiles/combined_sub.dir/compiler_depend.make

# Include the progress variables for this target.
include gelsight/CMakeFiles/combined_sub.dir/progress.make

# Include the compile flags for this target's objects.
include gelsight/CMakeFiles/combined_sub.dir/flags.make

gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o: gelsight/CMakeFiles/combined_sub.dir/flags.make
gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o: /home/xgy/ws_xgy/ws_project/qt_ros_hand/src/gelsight/src/combined_sub.cpp
gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o: gelsight/CMakeFiles/combined_sub.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xgy/ws_xgy/ws_project/qt_ros_hand/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o"
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o -MF CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o.d -o CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o -c /home/xgy/ws_xgy/ws_project/qt_ros_hand/src/gelsight/src/combined_sub.cpp

gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/combined_sub.dir/src/combined_sub.cpp.i"
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xgy/ws_xgy/ws_project/qt_ros_hand/src/gelsight/src/combined_sub.cpp > CMakeFiles/combined_sub.dir/src/combined_sub.cpp.i

gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/combined_sub.dir/src/combined_sub.cpp.s"
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xgy/ws_xgy/ws_project/qt_ros_hand/src/gelsight/src/combined_sub.cpp -o CMakeFiles/combined_sub.dir/src/combined_sub.cpp.s

# Object files for target combined_sub
combined_sub_OBJECTS = \
"CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o"

# External object files for target combined_sub
combined_sub_EXTERNAL_OBJECTS =

/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: gelsight/CMakeFiles/combined_sub.dir/src/combined_sub.cpp.o
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: gelsight/CMakeFiles/combined_sub.dir/build.make
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libcv_bridge.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libimage_transport.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libclass_loader.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/libPocoFoundation.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libdl.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libroslib.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/librospack.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libpython2.7.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libmessage_filters.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libroscpp.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/librosconsole.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/librostime.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /opt/ros/melodic/lib/libcpp_common.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
/home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub: gelsight/CMakeFiles/combined_sub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xgy/ws_xgy/ws_project/qt_ros_hand/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub"
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/combined_sub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gelsight/CMakeFiles/combined_sub.dir/build: /home/xgy/ws_xgy/ws_project/qt_ros_hand/devel/lib/gelsight/combined_sub
.PHONY : gelsight/CMakeFiles/combined_sub.dir/build

gelsight/CMakeFiles/combined_sub.dir/clean:
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight && $(CMAKE_COMMAND) -P CMakeFiles/combined_sub.dir/cmake_clean.cmake
.PHONY : gelsight/CMakeFiles/combined_sub.dir/clean

gelsight/CMakeFiles/combined_sub.dir/depend:
	cd /home/xgy/ws_xgy/ws_project/qt_ros_hand/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xgy/ws_xgy/ws_project/qt_ros_hand/src /home/xgy/ws_xgy/ws_project/qt_ros_hand/src/gelsight /home/xgy/ws_xgy/ws_project/qt_ros_hand/build /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight /home/xgy/ws_xgy/ws_project/qt_ros_hand/build/gelsight/CMakeFiles/combined_sub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gelsight/CMakeFiles/combined_sub.dir/depend

