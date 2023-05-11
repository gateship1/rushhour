#include "SetupDefaultBoard.hpp"


std::unique_ptr<Board> SetupDefaultBoard::build_starting_board() {

    return std::make_unique<Board>(
        initialize_vehicles(
            parse_board_string( DEFAULT_BOARD ) ) );

}
