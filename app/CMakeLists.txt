add_executable(test_graph test_graph.cpp)
target_link_libraries(test_graph pthread)

add_executable(test_any test_any.cpp)

add_executable(test_vtlogger test_vtlogger.cpp)

add_executable(test_type_deduction type_deduction.cpp)

