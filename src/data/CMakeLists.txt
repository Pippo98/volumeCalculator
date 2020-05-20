if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_library(data
            SHARED
            data.h
            data.cc
            type.h)