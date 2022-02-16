cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

project(Miniscience)
#add_executable(cubic2d Lab2/cubic2d.cpp)
#add_executable(cubic3d Lab2/cubic3d.cpp)
#add_executable(tetr3d Lab2/tetr3d.cpp)

# Найдём VTK
#find_package(VTK REQUIRED)
# ... и подключим её со всеми её компонентами её нативными средствами
#include(${VTK_USE_FILE})

# gmsh укажем явно по кусочкам (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/Users/arseniy/Documents/gmsh-4.9.4-MacOSX-sdk/lib/libgmsh.4.9.dylib"
    INTERFACE_INCLUDE_DIRECTORIES "/Users/arseniy/Documents/gmsh-4.9.4-MacOSX-sdk/include"
)
set(GMSH_LIBRARY gmsh)

# если бы gmsh был поставлен прилично, то можно было бы примерно вот так
#find_package(gmsh REQUIRED)
#include_directories(${GMSH_INCLUDE_DIR})
#target_link_libraries(tetr3d ${GMSH_LIBRARY})

# Укажем библиотеки для линковки
# ... тут только VTK
#target_link_libraries(cubic2d ${VTK_LIBRARIES})
#target_link_libraries(cubic3d ${VTK_LIBRARIES})
#
## ... а тут ещё и gmsh
#target_link_libraries(tetr3d ${VTK_LIBRARIES})
#target_link_libraries(tetr3d ${GMSH_LIBRARY})


add_executable(sample01 Lab1/sample01.cpp)
add_executable(sample02 Lab1/sample02.cpp)
add_executable(sample03 Lab1/sample03.cpp)
add_executable(sample04 Lab1/sample04.cpp)
add_executable(Epizode0 Lab1/Epizode0.cpp)
add_executable(Circle Lab1/Circle.cpp)
add_executable(Epizode1 Lab1/Epizode1.cpp)


# Укажем библиотеки для линковки
target_link_libraries(sample01 ${GMSH_LIBRARY})
target_link_libraries(sample02 ${GMSH_LIBRARY})
target_link_libraries(sample03 ${GMSH_LIBRARY})
target_link_libraries(sample04 ${GMSH_LIBRARY})
target_link_libraries(Epizode0 ${GMSH_LIBRARY})
target_link_libraries(Circle ${GMSH_LIBRARY})
target_link_libraries(Epizode1 ${GMSH_LIBRARY})
