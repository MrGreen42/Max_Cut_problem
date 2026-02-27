#include "max_cut_solver.hpp"
#include <cmath>
#include <random>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <omp.h>

namespace max_cut_solver {

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void Solver::solve() {
    best_maxcut = std::numeric_limits<int>::min();
    best_solution.clear();

    double p_value = solver_config.pi;
    double a_value = solver_config.alpha;
    double beta_value = 0.0;
    int curr_cut = 0;
    double time_last_improve = 0.0;
    int number_vert = graph.getVerticeNumber();
    std::vector<double> hamilt(number_vert);

    std::vector<double> x_values(number_vert);
    std::vector<double> delta_x(number_vert);
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> dist(0.0, 0.1);
    
    for (int i = 0; i < number_vert; ++i) {
        x_values[i] = dist(rng);
    }

    std::vector<double> e_values(number_vert, 1.0);
    std::vector<int> sigma(number_vert);
    double time = 0.0;
    
    while (time < solver_config.t_max) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            double sum = 0.0;
            for (int j = 0; j < number_vert; ++j) {
                sum += x_values[j] * graph.getValueIJ(i, j);
            }
            hamilt[i] = sum;
        }

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            delta_x[i] = solver_config.dt * (
                (p_value - 1.0) * x_values[i] -
                x_values[i] * x_values[i] * x_values[i] +
                solver_config.epsilon * e_values[i] * hamilt[i]
            );
        }

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            e_values[i] += solver_config.dt * (
                -beta_value * (x_values[i] * x_values[i] - a_value) * e_values[i]
            );
        }
        if (std::isnan(e_values[0])) {
            break;
        }

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            x_values[i] -= delta_x[i];
        }

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            sigma[i] = sgn(x_values[i]);
        }

        curr_cut = 0;
        #pragma omp parallel for reduction(+:curr_cut) schedule(static)
        for (int i = 0; i < number_vert; ++i) {
            for (int j = i + 1; j < number_vert; ++j) {
                if (graph.getValueIJ(i, j) != 0.0 && sigma[i] != sigma[j]) {
                    curr_cut += static_cast<int>(graph.getValueIJ(i, j));
                }
            }
        }

        if (curr_cut > best_maxcut) {
            best_maxcut = curr_cut;
            best_solution = sigma;
            time_last_improve = time;
        }
        
        double delta_C = static_cast<double>(best_maxcut - curr_cut);
        double phi = std::tanh(solver_config.delta * delta_C);

        a_value = solver_config.alpha - solver_config.rho * phi;
        p_value = solver_config.pi + solver_config.rho * phi;

        if (time - time_last_improve < solver_config.tau) {
            beta_value += solver_config.gamma * solver_config.dt;
        } else {
            beta_value = 0.0;
            time_last_improve = time;
        }
        time += solver_config.dt;
    }
}

SolverConfig create_solver_config(const graph_loader::Graph& graph) {
    SolverConfig cfg;
    const int N = graph.getVerticeNumber();

    double avg_sum = 0.0;
    for (int i = 0; i < N; ++i) {
        double sum_weights = 0.0;
        for (int j = 0; j < N; ++j) {
            sum_weights += std::abs(graph.getValueIJ(i, j));
        }
        avg_sum += sum_weights / N;
    }
    cfg.epsilon = 3.0 / avg_sum;
    
    Eigen::MatrixXd Omega = Eigen::MatrixXd::Zero(N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            Omega(i, j) = graph.getValueIJ(i, j);
        }
    }
    
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(Omega);
    
    Eigen::VectorXd evals = solver.eigenvalues();
    
    double nu1 = evals(N - 1);
    double nu2 = evals(N - 2);
    double nu3 = evals(N - 3);
    double nu4 = evals(N - 4);
    
    double g_val = -6.3674 - 0.2579 * nu1 - 1.0548 * nu2 
        - 4.2597 * nu3 + 6.1727 * nu4;
    cfg.pi = 1.0 - cfg.epsilon * g_val;
    
    cfg.alpha = 1.0;
    cfg.rho = 1.0;
    cfg.delta = 7.0;
    cfg.gamma = 0.065 / N;
    cfg.tau = 7.0 * N;
    
    cfg.dt = 0.05;
    cfg.t_max = 5.0 * cfg.tau;
    
    return cfg;
}
} // namespace max_cut_solver