#include "file_input.hpp"

#include <iostream>

/* read_input_file
  
  parameters:
    filename, the input file name and path to the file
  
  return:
    tstring, a single string representation of the input file text
*/
auto read_input_file(const std::string& filename) -> std::string {
    
    std::ifstream infile;
    infile.open(filename);
    std::string tstring, string_row;
    
    if (!infile.is_open()) {
        std::cout << "file is not open\n";
        return std::string{};
    } else {
        std::cout << "Reading => " << filename << "\n";
        while (getline(infile, string_row)) {
            tstring += string_row;
            tstring += '|';
        }
        infile.close();
        std::cout << "Input read.\n\n";
    }
    
    return tstring.substr(0, tstring.size() - 1); // pop off the last '|' to match the cmdline input format
}