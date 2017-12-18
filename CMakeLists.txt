cmake_minimum_required(VERSION 2.8.11)

project(sdlgl)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Force C++11
if(UNIX)
  SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

find_package(OpenGL)

find_package(SDL2 REQUIRED)
message(${SDL2_INCLUDE_DIRS})
include_directories( ${SDL2_INCLUDE_DIRS} )

# find_package(Qt5Widgets REQUIRED core opengl widgets gui )
# include_directories( ${Qt5Widgets_INCLUDE_DIRS} )
# include_directories( ${Qt5Widgets_LIBRARIES} )

set(GLM_DIR "${CMAKE_SOURCE_DIR}/glm/glm")

if(EXISTS "${GLM_DIR}")
    include_directories( "${GLM_DIR}" )
else()
    message( FATAL_ERROR "${GLM_DIR} doesn't exist, did you sync all submodules?" )
endif()

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

file(GLOB CPP_SOURCES 
		${CMAKE_SOURCE_DIR}/src/*.cpp
 	)

file(GLOB HEADERS 
    	${CMAKE_SOURCE_DIR}/include/*.h
  	)

file(GLOB VERTEX_SOURCES ${CMAKE_SOURCE_DIR}/shaders/*.frag)
file(GLOB FRAGMENT_SOURCES ${CMAKE_SOURCE_DIR}/shaders/*.vert)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
  )

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${HEADERS} ${VERTEX_SOURCES} ${FRAGMENT_SOURCES})

source_group("Shaders\\Vertex"  FILES ${VERTEX_SOURCES})
source_group("Shaders\\Fragment"  FILES ${FRAGMENT_SOURCES})

# target_link_libraries(romanesco SDL2 opengl32 OpenCL::OpenCL)
target_link_libraries(${PROJECT_NAME}
                    ${OPENGL_gl_LIBRARY}
                    ${Boost_LIBRARIES}
                    # ${Qt5Widgets_LIBRARIES}
                    ${SDL2_LIBRARIES}
									  )

# Windows specific build steps
# if(WIN32)
#     # Run winddeployqt if it can be found
#     find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
#     message( "Configuring Qt deployment with ${WINDEPLOYQT_EXECUTABLE}" )
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${PROJECT_NAME}>)
# endif()

# Copy resources to build folder (styles/, shaders/, kernel/, images/, scenes/)
# ToDo this doesn't automatically copy every build, but good enough if you're not doing kernel development
# add_custom_target(copy-runtime-files ALL
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/styles" "${PROJECT_BINARY_DIR}/styles"
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/shaders" "${PROJECT_BINARY_DIR}/shaders"
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/kernel" "${PROJECT_BINARY_DIR}/kernel"
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/images" "${PROJECT_BINARY_DIR}/images"
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/scenes" "${PROJECT_BINARY_DIR}/scenes"
#     COMMAND cmake -E copy_directory "${CMAKE_SOURCE_DIR}/hdr" "${PROJECT_BINARY_DIR}/hdr"
# )

# install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_BINARY_BIN}/bin)
