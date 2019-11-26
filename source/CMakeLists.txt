cmake_minimum_required(VERSION 3.0)
project(Calculater)
include_directories(./doctest/)
SET(CMAKE_CXX_FLAGS "-std=c++11")
add_compile_options(-Wall)
add_compile_options(-Wextra)

# use google test begin
#configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#  RESULT_VARIABLE result
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#  RESULT_VARIABLE result
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#if(result)
#  message(FATAL_ERROR "Build step for googletest failed: ${result}")
#endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                 ${CMAKE_BINARY_DIR}/googletest-build
#                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
#if (CMAKE_VERSION VERSION_LESS 2.8.11)
#  include_directories("${gtest_SOURCE_DIR}/include")
#endif()
# use google test end

SET(TOKEN_SOURCE token.h token.cpp calc_type_define.h)

SET(NUMBER_SOURCE token_number.h token_number.cpp ${TOKEN_SOURCE})

SET(OPERATOR_SRC token_operator.h token_operator.cpp ${NUMBER_SOURCE})

SET(ADD_OPER_SRC add_operator.h add_operator.cpp ${OPERATOR_SRC})

SET(SUB_OPER_SRC sub_operator.h sub_operator.cpp ${OPERATOR_SRC})

SET(MUL_OPER_SRC mul_operator.h mul_operator.cpp ${OPERATOR_SRC})

SET(DIV_OPER_SRC div_operator.h div_operator.cpp ${OPERATOR_SRC})

SET(PARSE_SRC    parse.h parse.cpp ${ADD_OPER_SRC} ${SUB_OPER_SRC} ${MUL_OPER_SRC} ${DIV_OPER_SRC})

SET(SOURCE_FILE main.cpp ${PARSE_SRC})

add_executable(calcu ${SOURCE_FILE})

SET(TEST_SOURCE_FILE calcu_doctest_test.cpp ${PARSE_SRC})

add_executable(testCalcu ${TEST_SOURCE_FILE})

#add_executable(calc_gtest calc_gtest_test.cpp ${PARSE_SRC})
#target_link_libraries(calc_gtest gtest_main)
if(USE_PVS_STUDIO)
    include(../PVS-Studio.cmake)
    pvs_studio_add_target(TARGET test2.analyze ALL
                      OUTPUT FORMAT errorfile
                      ANALYZE calcu
                      MODE GA:1,2 OP
                      LOG target.err
                      CONFIG "../PVS-Studio.cfg")
else()
endif()
add_custom_target(test2)
add_custom_command(TARGET test2 COMMAND ./testCalcu)

#add_custom_command(TARGET test2 COMMAND ./calc_gtest)
