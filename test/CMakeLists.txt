#add_executable(test_wigner_3nj test_wigner_3nj.cpp)

#add_executable(test_spherical_harmonic test_spherical_harmonic.cpp)

set(WIGNER_TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

add_executable(test_half_integer half_integer.cpp)
target_link_libraries(test_half_integer catch)

add_executable(test_gaunt gaunt.cpp)
target_link_libraries(test_gaunt catch)

add_test(NAME wigner_gaunt COMMAND test_gaunt ${CMAKE_CURRENT_SOURCE_DIR}/gaunt_lmax10)
add_test(NAME wigner_half_integer COMMAND test_half_integer)
