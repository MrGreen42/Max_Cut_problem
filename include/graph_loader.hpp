#pragma once
#include <vector>
#include <string>
#include <limits>

namespace graph_loader {

class Graph{
private:
    // Количество вершин
    int N = 0;
    // Количество ребер
    int M = 0;
    std::vector<std::vector<double>> weights;

public:
    Graph() = default;
    Graph(int number_vert, int number_edge, const std::vector<std::vector<double>>& weights_) : N(number_vert), M(number_edge), weights(weights_) {}
    int getEdgeNumber() {return M;}
    int getVerticeNumber() {return N;}
    double getValueIJ(int index1, int index2) {
        if (index1 < 0 || index1 >= N ||
        index2 < 0 || index2 >= N) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return weights[index1][index2];
    }
};

Graph readGraphFromFile(const std::string& filepath);

} // namespace graph_loader