# define minimum cmake version
cmake_minimum_required(VERSION 3.24)
project(GroupRotationApp)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

##_____________________________________________________________________________
## Please set your wxWidgets configuration here
##_____________________________________________________________________________

# Here you can define what libraries of wxWidgets you need for your
# application. You can figure out what libraries you need here;
# https://docs.wxwidgets.org/3.2/page_libs.html
# We need the Find package for wxWidgets to work
# NOTE: if you're using aui, include aui in this required components list.

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS core base REQUIRED)

##_____________________________________________________________________________
## Actual config file starts here
##_____________________________________________________________________________

# wxWidgets include (this will do all the magic to configure everything)
include("${wxWidgets_USE_FILE}")

set(SRCS GroupRotationApp.cpp GroupRotationClasses.cpp GroupRotationClasses.h)

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if (WIN32)
    set(SRCS ${SRCS} GroupRotationApp.rc GroupRotationApp.cpp GroupRotationClasses.cpp GroupRotationClasses.h)
endif(WIN32)

add_executable(${PROJECT_NAME} WIN32 ${SRCS})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

