#ifndef __SETUP_FROM_CMDLINE_H__
#define __SETUP_FROM_CMDLINE_H__

#include <string>

#include "Setup.hpp"

class SetupFromCmdLine : public Setup {

public:

    explicit SetupFromCmdLine(const std::string& board_string_);
    virtual ~SetupFromCmdLine() = default;

    SetupFromCmdLine(const SetupFromCmdLine&) = delete;
    SetupFromCmdLine(SetupFromCmdLine&&) = delete;

    static std::string clean_board_string(const std::string& board_string);

    virtual std::unique_ptr<Board> build_starting_board() override final;

protected:

    const std::string board_string;

};

#endif /* __SETUP_FROM_CMDLINE_H__ */
