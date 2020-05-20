if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_library(pangolin_viewer
            SHARED
            viewer.h
            viewer.cc)

find_package(Eigen3 REQUIRED)

target_link_libraries(pangolin_viewer
                      PUBLIC
                      pangolin
                      opencv_highgui
                      Eigen3::Eigen)