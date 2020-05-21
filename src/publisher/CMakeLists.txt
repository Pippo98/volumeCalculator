if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Add sources
add_library(publisher
            SHARED
            map_publisher.h
            map_publisher.cc)
