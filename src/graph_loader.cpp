#include "graph_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace graph_loader {

Graph readGraphFromFile(const std::string& filepath) {
    std::vector<std::vector<double>> weights;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    int number_vert, number_edge;
    if (!(file >> number_vert >> number_edge)) {
        throw std::runtime_error("Invalid data: number of vertices or number of edges");
    }
    weights.resize(number_vert);
    for (int i = 0; i < number_vert; ++i) {
        weights[i].resize(number_vert);
    }
    int vert1, vert2;
    double weight;
    while (file >> vert1 >> vert2 >> weight) {
        if (1 > vert1 || vert1 > number_vert ||
            1 > vert2 || vert2 > number_vert) {
                throw std::runtime_error("Invalid data: incorrect vertice index");
        }
        weights[vert1 - 1][vert2 - 1] = weight;
        weights[vert2 - 1][vert1 - 1] = weight;
    }
    return Graph{number_vert, number_edge, weights};
}

} // namespace graph_loader