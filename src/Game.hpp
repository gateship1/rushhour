#ifndef __GAME_H__
#define __GAME_H__

#include <memory>

#include "Board.hpp"

class Game {

protected:

    const std::unique_ptr<Board>& starting_board;

public:

    Game(const std::unique_ptr<Board>& board_);
    virtual ~Game() = default;

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    virtual void play() = 0;

};

#endif /* __GAME_H__ */
