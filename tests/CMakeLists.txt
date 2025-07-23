add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE NeneIcecream::NeneIcecream)
add_test(NAME sandbox COMMAND sandbox)
