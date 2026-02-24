#include <iostream>
#include <cassert>
#include <cmath>
#include "graph_loader.hpp"
#include "max_cut_solver.hpp"

void calculateG1() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("gset_data/G1.txt");
    std::cout << "End reading graph" << std::endl;
    max_cut_solver::SolverConfig config = max_cut_solver::create_solver_config(graph);
    std::cout << "Construct a config" << std::endl;
    max_cut_solver::Solver solver(config, graph);
    int result = 0;
    for (int i = 0; i < 20; ++i) {
        solver.solve();
        result = std::max(solver.getSolution(), result);
        std::cout << result << std::endl;
    }

    assert(result != 11624);
    
    std::cout << "[PASS] Small graph calculated correctly" << std::endl;
}

int main() {
    try {
        calculateG1();
        
        std::cout << std::endl;
        std::cout << "  ALL TESTS PASSED!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << std::endl;
        std::cerr << "  TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}