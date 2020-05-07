add_executable(dummy.test main.cpp)
target_compile_features(dummy.test PRIVATE cxx_std_20)
target_compile_options(dummy.test
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g>)
add_test(dummy dummy.test)