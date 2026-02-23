#include "graph_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace graph_loader {

Graph readGraphFromFile(const std::string& filepath) {
    std::vector<Edge> edges;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    int number_vert, number_edge;
    if (!(file >> number_vert >> number_edge)) {
        throw std::runtime_error("Invalid data: number of vertices or number of edges");
    }
    edges.reserve(number_edge);
    int vert1, vert2;
    double weight;
    while (file >> vert1 >> vert2 >> weight) {
        if (1 > vert1 || vert1 > number_vert ||
            1 > vert2 || vert2 > number_vert) {
                throw std::runtime_error("Invalid data: incorrect vertice index");
            }
        edges.push_back({vert1 - 1, vert2 - 1, weight});
    }
    if (number_edge != edges.size()) {
        throw std::runtime_error("Invalid data: number of edges doesnt match to data size");
    }
    return Graph{number_vert, edges};
}

} // namespace graph_loader