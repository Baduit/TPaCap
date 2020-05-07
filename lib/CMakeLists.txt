add_library(TPaCap INTERFACE ${SRCS})

target_compile_features(TPaCap INTERFACE cxx_std_20)

target_include_directories(TPaCap
                           INTERFACE
                           ${CMAKE_CURRENT_LIST_DIR})
