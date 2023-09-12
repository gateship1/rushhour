#include "AStar.hpp"
#include "SolverTests.hpp"

TEST_F(SolverTests, astar_solution_found) {

    initialize_default_board();

    auto starting_bitboard { game_board->get_state() };

    std::unique_ptr<Solver> astar { std::make_unique<AStar>(game_board, &player_heuristic_1D) };
    auto path { astar->solve() };

    uint64_t state { path.first->front()->get_state() };

    ASSERT_EQ( state, starting_bitboard );

    for (auto& board: *path.first) {
        state = board->get_state();
    }

    ASSERT_EQ( state & GOAL, GOAL );

}


TEST_F(SolverTests, astar_no_solution) {

    initialize_no_solution_board();

    std::unique_ptr<Solver> astar { std::make_unique<AStar>(game_board, &player_heuristic_1D) };
    auto path { astar->solve() };

    EXPECT_GT( path.second, 0 );

    ASSERT_EQ( path.first, nullptr );

}
