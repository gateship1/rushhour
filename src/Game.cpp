#include "Game.hpp"

Game::Game(const std::unique_ptr<Board>& board_) :
    starting_board( std::move(board_) ) {

}
