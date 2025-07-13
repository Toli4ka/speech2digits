set(USER_C_MODULES ${USER_C_MODULES} ${CMAKE_CURRENT_LIST_DIR})

add_library(usermod_tflm_predict INTERFACE)

target_sources(usermod_tflm_predict INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/modftlm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tflm_predict.cpp
)

target_include_directories(usermod_tflm_predict INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    /Users/anatolii/cpp_libs/tflite-micro
    /Users/anatolii/cpp_libs/flatbuffers/include
    /Users/anatolii/cpp_libs/gemmlowp
)
# Set C++11 explicitly only on the C++ sources via generator expressions
target_compile_options(usermod_tflm_predict INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
)

# Add QSTR definitions for this module
set(USER_C_MODULES_QSTR ${USER_C_MODULES_QSTR} ${CMAKE_CURRENT_LIST_DIR}/qstrdefs.txt PARENT_SCOPE)

target_link_libraries(usermod INTERFACE usermod_tflm_predict)