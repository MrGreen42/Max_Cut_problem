# Max_Cut_problem

Solver for the **MAX-CUT problem** with Ising model using the algorithm described in [arXiv:1810.12565](https://arxiv.org/pdf/1810.12565).

## Status

I didn't have time to finish it. I know this code needs significant refactoring, especially regarding:
- Optimization
- Documentation
- Testing
- Error handling

Also, results of the algorithm on the GSET benchmark don't yet match reference values. So right now, this code mainly represents the core idea of the algorithm.

# Run solver tests
./bin/test_max_cut

# Run graph loader tests
./bin/test_graph_loader

# Run CLI solver
./bin/Max_Cut_problem_cli

## Build

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DUSE_OPENMP=ON
make -j$(nproc)

