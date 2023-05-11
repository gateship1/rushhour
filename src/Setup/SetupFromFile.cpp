#include "SetupFromFile.hpp"

#include <fstream>
#include <iostream>


SetupFromFile::SetupFromFile(const std::string& filepath_) :
    filepath(filepath_) { }


std::unique_ptr<Board> SetupFromFile::build_starting_board() {

    return std::make_unique<Board>(
        initialize_vehicles(
            parse_board_string(
                return_board_string_from_input_file() ) ) );

}


std::string SetupFromFile::return_board_string_from_input_file() const {

    std::ifstream infile;
    infile.open(filepath);
    std::string starting_board_string, string_row;
    
    if (!infile.is_open()) {
        throw std::invalid_argument("file is not open\n");

    } else {

        std::cout << "Reading => " << filepath << "\n";
        while (getline(infile, string_row)) {
            starting_board_string += string_row;
        }
        infile.close();
        std::cout << "Input read.\n";

    }

    return starting_board_string;
}
