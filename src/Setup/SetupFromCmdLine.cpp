#include "SetupFromCmdLine.hpp"


SetupFromCmdLine::SetupFromCmdLine(const std::string& board_string_) :
    board_string( SetupFromCmdLine::clean_board_string(board_string_) ) {

}


std::unique_ptr<Board> SetupFromCmdLine::build_starting_board() {

    return std::make_unique<Board>(
        initialize_vehicles(
            parse_board_string(board_string) ) );

}


std::string SetupFromCmdLine::clean_board_string(const std::string& board_string) {

    std::string clean_string {  };

    for (char ch : board_string) {
        if (ch != '|') {
            clean_string += ch;
        }
    }

    return clean_string;

}
