#include <iostream>
#include <cassert>
#include <cmath>
#include "graph_loader.hpp"
#include "max_cut_solver.hpp"

void test_small_graph() {
    std::string pathfile= "test_data/tiny_graph.txt";
    graph_loader::Graph graph = graph_loader::readGraphFromFile(pathfile);

    max_cut_solver::SolverConfig config = max_cut_solver::create_solver_config(graph);

    max_cut_solver::Solver solver(config, graph);
    double accuracy = 0.0;
    int number_calculations = 1000;
    for (int i = 0; i < number_calculations; ++i) {
        solver.solve();
        if (solver.getSolution() == 4) {
            accuracy += 1.0;
        }
    }
    accuracy /= number_calculations;
    
    std::cout << "[PASS] Small graph calculated with accuracy " << accuracy << std::endl;
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