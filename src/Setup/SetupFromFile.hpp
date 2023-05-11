#ifndef __SETUP_FROM_FILE_H__
#define __SETUP_FROM_FILE_H__

#include <string>

#include "Setup.hpp"

class SetupFromFile : public Setup {


public:

    explicit SetupFromFile(const std::string& filepath_);
    virtual ~SetupFromFile() = default;

    SetupFromFile(const SetupFromFile&) = delete;
    SetupFromFile(SetupFromFile&&) = delete;

    virtual std::unique_ptr<Board> build_starting_board() override;

protected:

    const std::string filepath;
    virtual std::string return_board_string_from_input_file() const;

};

#endif /* __SETUP_FROM_FILE_H__ */
