set(USER_C_MODULES ${USER_C_MODULES} ${CMAKE_CURRENT_LIST_DIR})

add_library(usermod_sum_custom INTERFACE)

target_sources(usermod_sum_custom INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/sum_custom.cpp
)

target_include_directories(usermod_sum_custom INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Set C++11 explicitly only on the C++ sources via generator expressions
target_compile_options(usermod_sum_custom INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
)

target_link_libraries(usermod INTERFACE usermod_sum_custom)