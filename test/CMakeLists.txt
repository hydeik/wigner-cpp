#add_executable(test_wigner_3nj test_wigner_3nj.cpp)

#add_executable(test_spherical_harmonic test_spherical_harmonic.cpp)

set(WIGNER_TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

add_executable(test_half_integer half_integer.cpp)
target_link_libraries(test_half_integer catch)

add_executable(test_gaunt_table gaunt_table.cpp)
target_link_libraries(test_gaunt_table catch)

add_executable(test_wigner3j_j_rec wigner3j_j_rec.cpp)
target_link_libraries(test_wigner3j_j_rec catch)

add_executable(test_wigner3j_m_rec wigner3j_m_rec.cpp)
target_link_libraries(test_wigner3j_m_rec catch)

add_executable(test_gaunt_j_rec gaunt_j_rec.cpp)
target_link_libraries(test_gaunt_j_rec catch)

add_executable(test_gaunt_m_rec gaunt_m_rec.cpp)
target_link_libraries(test_gaunt_m_rec catch)

# Tests commands
add_test(NAME wigner_half_integer COMMAND test_half_integer)

add_test(NAME wigner_wigner3j_j_rec
    COMMAND test_wigner3j_j_rec --${WIGNER_TEST_DATA_DIR}/wigner3j_j_rec_jmax10)
add_test(NAME wigner_wigner3j_m_rec
    COMMAND test_wigner3j_m_rec --${WIGNER_TEST_DATA_DIR}/wigner3j_m_rec_jmax10)
add_test(NAME wigner_gaunt_j_rec
    COMMAND test_gaunt_j_rec --${WIGNER_TEST_DATA_DIR}/gaunt_j_rec_lmax10)
add_test(NAME wigner_gaunt_m_rec
    COMMAND test_gaunt_m_rec --${WIGNER_TEST_DATA_DIR}/gaunt_m_rec_lmax10)
add_test(NAME wigner_gaunt_table
    COMMAND test_gaunt_table --${WIGNER_TEST_DATA_DIR}/gaunt_lmax5)
