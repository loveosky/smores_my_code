cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#project(smore_control)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_BUILD_TYPE Debug)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()


include(FindBoost)
find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex thread)
find_package(Protobuf REQUIRED)
find_package(Threads)
find_package(OpenGL)
find_package(GLUT)
find_package(Qt4 REQUIRED)
# find_package(OGRE REQUIRED)

#--------- QT GUI STUFF
set(smores_gui_SOURCES smorescontrollerwindow.cpp)
set(smores_gui_HEADERS smorescontrollerwindow.h)
set(smores_gui_FORMS smorescontrollerwindow.ui)
QT4_WRAP_CPP(smores_gui_HEADERS_MOC ${smores_gui_HEADERS})
QT4_WRAP_UI(smores_gui_FORMS_HEADERS ${smores_gui_FORMS})
include(${QT_USE_FILE})
add_library(smores_gui ${smores_gui_SOURCES}
    ${smores_gui_HEADERS_MOC}
    ${smores_gui_FORMS_HEADERS})
target_link_libraries(smores_gui ${QT_LIBRARIES})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#--------- END OF QT GUI STUFF

add_subdirectory(../../SimulationPlugins/MessageDefinition MessageDefinition)


include_directories(
  extern/glew-1.10.0/include/
)

# GLEW Portions
set(GLEW_SOURCE
  extern/glew-1.10.0/src/glew.c
)

set(GLEW_HEADERS)
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
)

add_library(GLEW_1100 STATIC
  ${GLEW_SOURCE}
  ${GLEW_INCLUDE}
)
target_link_libraries(GLEW_1100 ${OPENGL_LIBRARY})
# #END of GLEW
 
#------- OCTOMAP Portion
include_directories(
	include/
)
set(OCTOMAP_LIBRARIES
	${CMAKE_SOURCE_DIR}/lib/liboctomap.a
	${CMAKE_SOURCE_DIR}/lib/liboctomath.a
)
#------- END OCTOMAP

 
#------- PCL Portions
find_package(PCL 1.3 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
#------- PCL PORTIONS END

set(GLLib ${OPENGL_LIBRARY} ${GLUT_Xi_LIBRARY} ${GLUT_Xmu_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_1100}) 

add_library(PCL_OCTREE pcl_octree_impl.cpp)
target_link_libraries(PCL_OCTREE ${PCL_LIBRARIES} ${OCTOMAP_LIBRARIES})

add_library(GLViewer GLViewer.cpp zpr.c)
target_link_libraries(GLViewer GLEW_1100 glut PCL_OCTREE)


include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/MessageDefinition)

include_directories(
        ${GAZEBO_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}/MessageDefinition
)
link_directories(${GAZEBO_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/MessageDefinition)

add_executable(smore_control main.cpp)
target_link_libraries(smore_control GLViewer smores_gui command_message
        ${Boost_LIBRARIES}
        ${GLLib}
        ${GAZEBO_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${QT_LIBRARIES}
        /usr/lib/libtbb.so.2
        )
add_dependencies(smore_control command_message)
