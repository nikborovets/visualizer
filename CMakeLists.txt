cmake_minimum_required(VERSION 3.10)
project(STLRenderer)

set(CMAKE_CXX_STANDARD 17)

# путь к каталогу, где лежит VTK
set(VTK_DIR "/usr/local/lib/cmake/vtk-9.3")

find_package(VTK REQUIRED COMPONENTS 
  CommonCore
  CommonDataModel
  IOGeometry
  RenderingCore
  RenderingOpenGL2
  InteractionStyle
)

if(NOT VTK_FOUND)
  message(FATAL_ERROR "Cannot find VTK")
endif()

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(STLRenderer
  src/main.cpp
  src/stlreader.cpp
  src/renderer.cpp 
  src/interactor_style.cpp
  src/scene_manager.cpp
)
target_link_libraries(STLRenderer ${VTK_LIBRARIES} OpenMP::OpenMP_CXX)

vtk_module_autoinit(
  TARGETS STLRenderer
  MODULES ${VTK_LIBRARIES}
)
