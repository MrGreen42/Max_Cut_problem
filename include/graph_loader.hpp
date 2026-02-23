#pragma once
#include <vector>
#include <string>

namespace graph_loader {
struct Edge{
    // Индексы вершин
    int vert1 = 0; // откуда
    int vert2 = 0; // куда
    double weight = 0; // вес ребра
};

class Graph{
private:
    // Количество вершин
    int N = 0;
    std::vector<Edge> edges;

public:
    Graph() = default;
    Graph(int number, std::vector<Edge> edg) : N(number), edges(edg) {}
    int getEdgeNumber() {return edges.size();}
};

Graph readGraphFromFile(const std::string& filepath);

} // namespace graph_loader