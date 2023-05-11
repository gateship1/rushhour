#include <string>
#include <sstream>

#include "RandomWalk.hpp"
#include "SetupDefaultBoard.hpp"
#include "SetupFromCmdLine.hpp"
#include "Solver.hpp"
#include "UnitTest.hpp"


TEST_F(UnitTest, random_walk_solution_found) {

    SetupFromCmdLine board_setup("  o aa|  o   |  oxx |ppp  q|     q|     q");
    std::unique_ptr<Board> board { board_setup.build_starting_board() };

    unsigned int seed { 1683814669 };

    std::string expected_seed_printout { "Seed for random walk: " + std::to_string(seed) };

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    std::unique_ptr<Solver> random { std::make_unique<RandomWalk>( board, 10, std::make_unique<unsigned int>(seed)) };

    std::string text { buffer.str() };
    auto result { text.compare(expected_seed_printout) };

    std::cout.rdbuf(prevcoutbuf);

    EXPECT_TRUE( result );

    auto path { random->solve() };

    EXPECT_EQ( path.second, 1 );

    bool state { path.first->front()->is_solution_state() };

    for (auto& board_state: *path.first) {
        state = board_state->is_solution_state();
    }

    ASSERT_TRUE( state );

}


TEST_F(UnitTest, random_walk_solution_not_found) {

    SetupDefaultBoard board_setup;
    std::unique_ptr<Board> board { board_setup.build_starting_board() };

    unsigned int seed { 1683815084 };

    std::string expected_seed_printout { "Seed for random walk: " + std::to_string(seed) };

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    std::unique_ptr<Solver> random { std::make_unique<RandomWalk>( board, 10, std::make_unique<unsigned int>(seed)) };

    std::string text { buffer.str() };
    auto result { text.compare(expected_seed_printout) };

    std::cout.rdbuf(prevcoutbuf);

    EXPECT_TRUE( result );

    auto path { random->solve() };

    EXPECT_EQ( path.second, 10 );

    bool state { path.first->front()->is_solution_state() };

    for (auto& board_state: *path.first) {
        state = board_state->is_solution_state();
    }

    ASSERT_FALSE( state );

}
