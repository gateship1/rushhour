#ifndef __SETUP_DEFAULT_BOARD_H__
#define __SETUP_DEFAULT_BOARD_H__

#include <string>

#include "Setup.hpp"

class SetupDefaultBoard : public Setup {

public:

    SetupDefaultBoard() = default;
    virtual ~SetupDefaultBoard() = default;

    SetupDefaultBoard(const SetupDefaultBoard&) = delete;
    SetupDefaultBoard(SetupDefaultBoard&&) = delete;
    SetupDefaultBoard& operator=(const SetupDefaultBoard&) = delete;
    SetupDefaultBoard& operator=(SetupDefaultBoard&&) = delete;

    virtual std::unique_ptr<Board> build_starting_board() override final;

private:

    const std::string DEFAULT_BOARD { "  o aa  o   xxo   ppp  q     q     q" };


};

#endif /* __SETUP_DEFAULT_BOARD_H__ */
