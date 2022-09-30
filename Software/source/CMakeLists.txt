cmake_minimum_required (VERSION 3.4)
project (korotkovAutomata CXX)
# add seqan3 to search path
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../seqan3/build_system")
 
# require seqan3 with a version between >=3.0.0 and <4.0.0
find_package (seqan3 3.0 REQUIRED)

set(SOURCES main.cpp nfa_pointer.cpp korotkov_nfa.cpp graphMaker.cpp utils.cpp)
set(BENCH benchmark_main.cpp nfa_pointer.cpp)
# build app with seqan3
add_executable(korotkov ${PROJECT_SOURCE_DIR}/${SOURCES})
target_link_libraries (korotkov seqan3::seqan3)

add_executable(benchmark ${PROJECT_SOURCE_DIR}/${BENCH})