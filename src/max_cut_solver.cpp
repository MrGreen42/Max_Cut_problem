#include "max_cut_solver.hpp"
#include <cmath>
#include <random>

namespace max_cut_solver {

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void Solver::solve() {
    double p_value = solver_config.pi;
    double a_value = solver_config.alpha;
    double beta_value = 0.0;
    int curr_cut = 0; // TODO: подумать почему не оценка снизу для данной задачи
    double time_last_improve = 0.0;
    int number_vert = graph.getVerticeNumber();
    std::vector<double> hamilt(number_vert);

    std::vector<double> x_values(number_vert);
    std::random_device rd;  // Источник энтропии ОС
    std::mt19937 rng(rd()); // Генератор без фиксированного seed
    std::normal_distribution<double> dist(0.0, 0.2);
    
    for (int i = 0; i < number_vert; ++i) {
        x_values[i] = dist(rng);
    }

    std::vector<double> e_values(number_vert, 1.0);
    std::vector<int> sigma(number_vert);
    double time = 0.0;
    while (time < solver_config.t_max) {
        for (int i = 0; i < number_vert; ++i) {
            hamilt[i] = 0.0;
            for (int j = 0; j < number_vert; ++j) {
                hamilt[i] += x_values[j] * graph.getValueIJ(i, j);
            }
        }
        for (int i = 0; i < number_vert; ++i) {
            x_values[i] += solver_config.dt * ((p_value - 1) * x_values[i] -
            x_values[i] * x_values[i] * x_values[i] +
            solver_config.epsilon * e_values[i] * hamilt[i]);
        }

        for (int i = 0; i < number_vert; ++i) {
            e_values[i] += solver_config.dt * (-beta_value *
                (x_values[i] * x_values[i] - a_value) * e_values[i]);
        }

        for (int i = 0; i < number_vert; ++i) {
            sigma[i] = sgn(x_values[i]);
        }

        curr_cut = 0;
        for (int i = 0; i < number_vert; ++i) {
            for (int j = i+1; j < number_vert; ++j) {
                if (graph.getValueIJ(i,j) != 0 && sigma[i] != sigma[j]) {
                    curr_cut += graph.getValueIJ(i,j);
                }
            }
        }

        if (curr_cut > best_maxcut) {
            best_maxcut = curr_cut;
            best_solution = sigma;
            time_last_improve = time;
        }
        double delta_C = best_maxcut - curr_cut;
        double phi = std::tanh(solver_config.delta * delta_C); // написать tanh самим, чтобы не подключать библиотеку
        a_value = solver_config.alpha - solver_config.rho * phi;
        p_value = solver_config.pi + solver_config.rho * phi;

        if (time - time_last_improve < solver_config.tau) {
            beta_value += solver_config.gamma * solver_config.dt;
        }
        else {
            beta_value = 0.0;
            time_last_improve = time;
        }
        time += solver_config.dt;
    }
}
} // namespace max_cut_solver