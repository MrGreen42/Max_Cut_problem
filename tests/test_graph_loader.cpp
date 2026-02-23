#include <iostream>
#include <cassert>
#include <cmath>
#include "graph_loader.hpp"

void test_load_tiny_graph() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("test_data/tiny_graph.txt");
    
    std::cout << "[PASS] Tiny graph loaded correctly" << std::endl;
}

void test_load_small_graph() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("test_data/small_graph.txt");
    
    std::cout << "[PASS] Small graph loaded correctly" << std::endl;
}

void test_invalid_graph() {
    bool exception_thrown = false;
    try {
        graph_loader::Graph graph = graph_loader::readGraphFromFile("test_data/invalid_graph_.txt");
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }
    
    assert(exception_thrown);
    std::cout << "[PASS] Invalid graph handled correctly" << std::endl;
}

void test_nonexistent_file() {
    bool exception_thrown = false;
    try {
        graph_loader::Graph graph = graph_loader::readGraphFromFile("test_data/does_not_exist.txt");
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }
    
    assert(exception_thrown);
    std::cout << "[PASS] Nonexistent file handled correctly" << std::endl;
}

int main() {
    try {
        test_load_tiny_graph();
        test_load_small_graph();
        test_invalid_graph();
        test_nonexistent_file();
        
        std::cout << std::endl;
        std::cout << "  ALL TESTS PASSED!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << std::endl;
        std::cerr << "  TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}