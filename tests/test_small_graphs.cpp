#include <iostream>
#include <cassert>
#include <cmath>
#include "graph_loader.hpp"
#include "max_cut_solver.hpp"

void test_small_graph() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("test_data/tiny_graph.txt");

    max_cut_solver::SolverConfig config = max_cut_solver::create_solver_config(graph);

    max_cut_solver::Solver solver(config, graph);
    solver.solve();
    int result = solver.getSolution();

    assert(result == 4);
    
    std::cout << "[PASS] Small graph calculated correctly" << std::endl;
}

int main() {
    try {
        test_small_graph();
        
        std::cout << std::endl;
        std::cout << "  ALL TESTS PASSED!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << std::endl;
        std::cerr << "  TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}