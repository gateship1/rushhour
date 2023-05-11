#include "BFS.hpp"
#include "Solver.hpp"
#include "UnitTest.hpp"


TEST_F(UnitTest, bfs_solution_found) {

    initialize_default_board();

    auto starting_bitboard { game_board->get_state() };

    std::unique_ptr<Solver> bfs { std::make_unique<BFS>(game_board) };
    auto path { bfs->solve() };

    EXPECT_GT( path.second, 0 );

    uint64_t state { path.first->front()->get_state() };

    ASSERT_EQ( state, starting_bitboard );

    for (auto& board: *path.first) {
        state = board->get_state();
    }

    ASSERT_EQ( state & GOAL, GOAL );

}


TEST_F(UnitTest, bfs_no_solution) {

    initialize_no_solution_board();

    std::unique_ptr<Solver> bfs { std::make_unique<BFS>(game_board) };
    auto path { bfs->solve() };

    EXPECT_GT( path.second, 0 );

    ASSERT_EQ( path.first, nullptr );

}
