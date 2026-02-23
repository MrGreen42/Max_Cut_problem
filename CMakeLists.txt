cmake_minimum_required(VERSION 3.16)
project(IsingAnalogSolver VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции
option(BUILD_TESTS "Build unit tests" ON)
option(USE_OPENMP "Enable OpenMP" ON)

# Основная библиотека
add_library(Max_Cut_problem STATIC
    src/max_cut_solver.cpp
    src/graph_loader.cpp
)

target_include_directories(Max_Cut_problem PUBLIC include)

if(USE_OPENMP)
    find_package(OpenMP REQUIRED)
    target_link_libraries(Max_Cut_problem PUBLIC OpenMP::OpenMP_CXX)
endif()

# CLI приложение
add_executable(Max_Cut_problem_cli apps/main.cpp)
target_link_libraries(Max_Cut_problem_cli PRIVATE Max_Cut_problem)
set_target_properties(Max_Cut_problem_cli PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Тесты
if(BUILD_TESTS)
    enable_testing()
    
    add_executable(test_max_cut
        tests/test_small_graphs.cpp
    )
    target_link_libraries(test_max_cut PRIVATE Max_Cut_problem)
    set_target_properties(test_max_cut PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    
    # Регистрация теста в CTest
    add_test(NAME SmallGraphsTest COMMAND test_max_cut)
endif()