add_subdirectory(data)
add_subdirectory(publisher)
add_subdirectory(pangolin_viewer)

set(EXECUTABLE_TARGETS "")

add_executable(main main.cc)
list(APPEND EXECUTABLE_TARGETS main)

foreach(EXECUTABLE_TARGET IN LISTS EXECUTABLE_TARGETS)
    # Link viewer
    target_link_libraries(${EXECUTABLE_TARGET} PRIVATE pangolin_viewer)
    target_link_libraries(${EXECUTABLE_TARGET} PRIVATE publisher)
    target_link_libraries(${EXECUTABLE_TARGET} PRIVATE data)
    # Link to required libraries

endforeach()