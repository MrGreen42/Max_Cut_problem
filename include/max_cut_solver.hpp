#pragma once
#include "graph_loader.hpp"

namespace max_cut_solver {
struct SolverConfig {
    // параметры задачи
    double epsilon = 0; // coupling strength
    double alpha = 0; // target amplitude baseline
    double pi = 0; // linear gain baseline
    double rho = 0; // amplitude and gain variation
    double delta = 0; // чувствительность к вариациям
    double gamma = 0; // скорость увеличения параметра beta
    double tau = 0; // максимально время без изменений

    // настройки солвера
    double t_max = 0; // макисмальное время
    double dt = 0; // временной шаг
};

class Solver {
private:
    SolverConfig solver_config;
    graph_loader::Graph graph;
    int best_maxcut = std::numeric_limits<int>::min();
    std::vector<int> best_solution;

public:
    void solve();
    int getSolution() {return best_maxcut;};
    Solver(const SolverConfig& config, const graph_loader::Graph& graph_) : solver_config(config), graph(graph_) {}
};

SolverConfig create_solver_config(const graph_loader::Graph& graph);
} // namespace max_cut_solver