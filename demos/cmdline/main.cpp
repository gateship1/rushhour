#include <iostream>

#include "file_input.hpp"
#include "game.hpp"
#include "run_demo.hpp"

auto main(int argc, char** argv) -> int {
    
    // check for command line input (cli) arguments
    if (argc > 1) {
        
        if (argc > 2) {
            
            if (static_cast<std::string>(argv[1]) == "file") {
                
                if (argc < 4) {
                    std::cout << "not enough arguments\n";
                    return -1;
                }                    
                auto board_str{read_input_file(argv[2])};
                
                if (board_str.empty()) {
                    std::cout << "check input file and path\n";
                    return -1;
                }
                Game game(board_str); // instantiate new game object with cli board
                
                if (game.retrieve_initial_board().get_width() == 0) {
                    std::cout << "board width is irregular (not all rows same width)\n";
                    return -1;
                    
                } else if (game.retrieve_initial_board().get_vehicles().empty()) {
                    std::cout << "vehicle error - illegal board configuration"
                              << "player vehicle not found or incorrectly positioned on board\n"
                              << "                (may be blocked by another horizontally oriented vehicle)\n";
                    return -1;
                }
                run_demo(argv[3], game);
                
            } else {
                // board is to be built from the cli string
                std::string cli_board_str{argv[2]};
                Game game(cli_board_str); // instantiate new game object with cli board
                
                if (game.retrieve_initial_board().get_width() == 0) {
                    std::cout << "board width is irregular (not all rows same width)\n";
                    return -1;
                    
                } else if (game.retrieve_initial_board().get_vehicles().empty()) {
                    std::cout << "vehicle error - illegal board configuration"
                              << "player vehicle not found or incorrectly positioned on board\n"
                              << "                (may be blocked by another horizontally oriented vehicle)\n";
                    return -1;
                }
                run_demo(argv[1], game);
            }
            
        } else {
            Game game; // instantiate new game object with default board
            run_demo(argv[1], game);
        }
        
    } else {
        std::cout << "Not enough arguments!\n";
        return -1;
    }
    
    return 0;
}
