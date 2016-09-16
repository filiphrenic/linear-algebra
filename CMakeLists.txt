cmake_minimum_required(VERSION 3.3)
project(linalg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Poly.h Vertex3D.h Face3D.h IRG.h ObjectModel.h AbstractVector.cpp AbstractVector.h IVector.cpp IVector.h IMatrix.cpp IMatrix.h Vector.cpp Vector.h AbstractMatrix.cpp AbstractMatrix.h MatrixTransposeView.cpp MatrixTransposeView.h MatrixSubmatrixView.cpp MatrixSubmatrixView.h MatrixVectorView.cpp MatrixVectorView.h VectorMatrixView.cpp VectorMatrixView.h Matrix.cpp Matrix.h)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if (NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif (NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

#########################################################
# Include Files
#########################################################
add_executable(linalg ${SOURCE_FILES})

########################################################
# Linking & stuff
#########################################################
target_link_libraries(linalg ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
