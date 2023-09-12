#include "DFS.hpp"
#include "SolverTests.hpp"


TEST_F(SolverTests, dfs_solution_found) {

    initialize_default_board();

    auto starting_bitboard { game_board->get_state() };

    std::unique_ptr<Solver> dfs { std::make_unique<DFS>(game_board) };
    auto path { dfs->solve() };

    EXPECT_GT( path.second, 0 );

    uint64_t state { path.first->front()->get_state() };

    ASSERT_EQ( state, starting_bitboard );

    for (auto& board: *path.first) {
        state = board->get_state();
    }

    ASSERT_EQ( state & GOAL, GOAL );

}


TEST_F(SolverTests, dfs_no_solution) {

    initialize_no_solution_board();

    std::unique_ptr<Solver> dfs { std::make_unique<DFS>(game_board) };
    auto path { dfs->solve() };

    EXPECT_GT( path.second, 0 );

    ASSERT_EQ( path.first, nullptr );

}
