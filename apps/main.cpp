#include <iostream>
#include <cassert>
#include <cmath>
#include "graph_loader.hpp"
#include "max_cut_solver.hpp"

void calculateG1() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("gset_data/G1.txt");
    //std::cout << "End reading graph" << std::endl;
    max_cut_solver::SolverConfig config = max_cut_solver::create_solver_config(graph);
    //std::cout << "Construct a config" << std::endl;
    max_cut_solver::Solver solver(config, graph);
    int result = 0;
    for (int i = 0; i < 20; ++i) {
        solver.solve();
        result = std::max(solver.getSolution(), result);
    }

    if (result != 11624) {
        throw std::runtime_error("Invalid answer: correct answer is 11624, but my is " + std::to_string(result)); 
    }
    
    std::cout << "[PASS] Small graph calculated correctly" << std::endl;
}

void calculateG2() {
    graph_loader::Graph graph = graph_loader::readGraphFromFile("gset_data/G2.txt");
    //std::cout << "End reading graph" << std::endl;
    max_cut_solver::SolverConfig config = max_cut_solver::create_solver_config(graph);
    //std::cout << "Construct a config" << std::endl;
    max_cut_solver::Solver solver(config, graph);
    int result = 0;
    for (int i = 0; i < 20; ++i) {
        solver.solve();
        result = std::max(solver.getSolution(), result);
    }

    if (result != 11624) {
        throw std::runtime_error("Invalid answer: correct answer is 11620, but my is " + std::to_string(result)); 
    }
    
    std::cout << "[PASS] Small graph calculated correctly" << std::endl;
}

int main() {
    try {
        calculateG1();
        calculateG2();
        
        std::cout << std::endl;
        std::cout << "  ALL TESTS PASSED!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << std::endl;
        std::cerr << "  TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}