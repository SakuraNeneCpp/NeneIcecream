add_executable(test_ic test.cpp)
target_link_libraries(test_ic PRIVATE NeneIcecream::NeneIcecream)
add_test(NAME test_ic COMMAND test_ic)
