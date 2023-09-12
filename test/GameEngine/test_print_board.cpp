#include "GameEngineTests.hpp"

#include <string>
#include <sstream>

#include "Board.hpp"
#include "HorizontalVehicle.hpp"
#include "make.hpp"
#include "PlayerVehicle.hpp"
#include "SetupDefaultBoard.hpp"
#include "Vehicle.hpp"
#include "VerticalVehicle.hpp"


TEST_F(GameEngineTests, print_board) {

    initialize_sample_board3();

    std::string expected_printout { "\n ------ \n|aabbco|\n|d eeco|\n|dfpxxo \n| fpqqq|\n|  p   |\n|hh    |\n ------ " };
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    game_board->print();

    std::string text = buffer.str();
    auto result = text.compare(expected_printout);

    std::cout.rdbuf(prevcoutbuf);

    ASSERT_FALSE(result);
}


TEST_F(GameEngineTests, print_default_board) {

    initialize_default_board();

    std::string expected_printout_default { "\n ------ \n|  o aa|\n|  o   |\n|xxo   \n|ppp  q|\n|     q|\n|     q|\n ------ \n|" };
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    game_board->print();

    std::string text { buffer.str() };
    auto result { text.compare(expected_printout_default) };

    std::cout.rdbuf(prevcoutbuf);

    ASSERT_TRUE(result);

}
