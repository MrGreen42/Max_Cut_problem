# Max_Cut_problem
Solver for MAX-CUT problem with Ising model using algorithm described in https://arxiv.org/pdf/1810.12565. It is a test task

I didn't have time to finish it, i know this code need much refactoring, especialy about optimization, documentation, testing and error handling. Also results of algorithm on benchmark GSET doesnt match to reference values. So right now this code mainly only represents idea of algorithm.

to build:
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DUSE_OPENMP=ON
    make -j$(nproc)

to run:
    ./bin/test_max_cut
        or
    ./bin/test_graph_loader
        or
    ./bin/Max_Cut_problem_cli


