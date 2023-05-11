#include "UnitTest.hpp"

#include <memory>
#include <vector>

#include "Board.hpp"
#include "make.hpp"


void check_next_boards(const std::forward_list<std::unique_ptr<Board>>& next_boards, const std::vector<uint64_t>& expected_boards) {

    uint8_t i { };
    for ( const auto& boards : next_boards ) {
        ASSERT_TRUE( std::find( expected_boards.begin(), expected_boards.end(), boards->get_state() ) != expected_boards.end() );
        ++i;
    }

    ASSERT_EQ(i, expected_boards.size());

}


TEST_F(UnitTest, next_boards_default_board) {
    
    initialize_default_board();

    auto next_boards { game_board->next() };

    std::vector<uint64_t> expected_boards {
        0b1111'1111'1001'1101'1001'0001'1111'0000'1111'0011'1000'0011'1000'0011'1111'1111,
        0b1111'1111'1001'0111'1001'0001'1111'0000'1011'1011'1000'0011'1000'0011'1111'1111,
        0b1111'1111'1001'0111'1001'0001'1111'0000'1001'1111'1000'0011'1000'0011'1111'1111,
        0b1111'1111'1001'0111'1001'0001'1111'0010'1111'0011'1000'0011'1000'0001'1111'1111,
        0b1111'1111'1001'0111'1001'0011'1111'0010'1111'0011'1000'0001'1000'0001'1111'1111
    };

    check_next_boards(next_boards, expected_boards);

}


TEST_F(UnitTest, next_boards_player_vehicle_only) {

    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000'0000)
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    auto board ( std::make_unique<Board>(make<vehicle_list>( std::move(player_vehicle) ) ) );

    uint64_t initial_board_state { 0b1111'1111'1000'0001'1000'0001'1011'0000'1000'0001'1000'0001'1000'0001'1111'1111 };

    check_board_state(board, initial_board_state);

    auto next_boards { board->next() };

    std::vector<uint64_t> expected_boards {
        0b1111'1111'1000'0001'1000'0001'1001'1000'1000'0001'1000'0001'1000'0001'1111'1111,
        0b1111'1111'1000'0001'1000'0001'1000'1100'1000'0001'1000'0001'1000'0001'1111'1111,
        0b1111'1111'1000'0001'1000'0001'1000'0110'1000'0001'1000'0001'1000'0001'1111'1111,
        0b1111'1111'1000'0001'1000'0001'1110'0000'1000'0001'1000'0001'1000'0001'1111'1111
    };

    check_next_boards(next_boards, expected_boards);

}


TEST_F(UnitTest, next_boards_sample_board) {

    initialize_sample_board1();

    auto next_boards { game_board->next() };

    std::vector<uint64_t> expected_boards {
        0b1111'1111'1000'1111'1111'0101'1110'0110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1011'1001'1111'0101'1110'0110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1111'0001'1111'0101'1110'0110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1011'1101'1110'0110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0101'1011'0110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0101'1001'1110'1111'0111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0101'1110'0110'1011'1111'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0111'1110'0110'1111'0101'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1111'1111'0111'1110'0100'1111'0101'1101'0111'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0101'1110'0110'1111'0111'1101'1101'1101'0111'1111'1111,
        0b1111'1111'1001'1101'1111'0101'1110'0110'1111'0111'1101'0111'1101'1101'1111'1111
    };

    check_next_boards(next_boards, expected_boards);

}
