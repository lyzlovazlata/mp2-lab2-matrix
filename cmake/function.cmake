function(create_project_lib TARGET )
    file(GLOB_RECURSE TARGET_SRC "*.c*")
    file(GLOB_RECURSE TARGET_HD "*.h*")
    add_library(${TARGET} STATIC ${TARGET_SRC} ${TARGET_HD})

    get_property ( LIB_LIST GLOBAL PROPERTY LIBS_P)
    list(APPEND LIB_LIST ${TARGET})
    set_property ( GLOBAL PROPERTY LIBS_P ${LIB_LIST})

    get_property ( LIB_I_LIST GLOBAL PROPERTY LIBS_I_P)
    list(APPEND LIB_I_LIST ${CMAKE_CURRENT_SOURCE_DIR})
    set_property ( GLOBAL PROPERTY LIBS_I_P ${LIB_ILIST})
endfunction()




function(create_executable_test_project TARGET) 
file (GLOB_RECURSE TARGET_SRC "*.c*") 
file (GLOB_RECURSE TARGET_HD "*.h*")
add_executable( ${TARGET} ${TARGET_SRC} ${TARGET_HD})

get_property ( LIB_LIST GLOBAL PROPERTY LIBS_P) 
target_link_libraries(${TARGET} gtest ${LIB_LIST})

get_property ( LIB_I_LIST GLOBAL PROPERTY LIBS_I_P) 
target_include_directories (${TARGET} PUBLIC ${LIB_I_LIST})

add_test(NAME ${TARGET} COMMAND ${TARGET}) 
endfunction()
