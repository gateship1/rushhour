#include "run_demo.hpp"

/* initial_board_config
  
  display initial game board configuration to the terminal
  
  parameters:
    game, the game object being played
*/
auto initial_board_config(Game& game) -> void {
    
    std::cout << "Board configuration:" << game.retrieve_initial_board();
    return;
}

/* print_solution
  
  display the solution to the terminal
  
  parameters:
    solution, the solution to display
*/
auto print_solution(const std::pair<Path<Board>, size_t>& solution) -> void {
    
    if (solution.first.path_objects.empty()) {
        std::cout << "Solution could not be found.\n"
                  << solution.second << " moves explored.\n";
    } else {
        std::cout << "Solution found!\n"
                  << solution.second << " moves explored.\n"
                  << "Solution path:\n";
        Board::print_path(solution.first.path_objects);
    }
    return;
}

/* run_demo
  
  runs a demonstration of the various algorithms via the command line
  
  parameters:
    arg, the command line argument that tells the demo "how to run"
    game, the game to run the arg on
*/
auto run_demo(const char* arg, Game& game) -> void {
    
    std::string clicmd{arg};
    
    // handle various cli commands
    if (clicmd == "print")
        initial_board_config(game);
    
    else if (clicmd == "done") {
        initial_board_config(game);
        std::cout << "Solution state? " << std::boolalpha 
                  << game.retrieve_initial_board().is_solution_state()
                  << std::noboolalpha << "\n";
    }
    
    else if (clicmd == "next") {
        auto next_boards{game.retrieve_initial_board().next()};
        Board::print_board_set(next_boards);
    
    // search for solutions
    } else if (clicmd == "random") { // random walk
        initial_board_config(game);
        auto solution{random_walk<Board>(game.retrieve_initial_board())};
        std::cout << "Seed: " << solution.second << '\n';
        Board::print_path(solution.first.path_objects);
    
    } else if (clicmd == "bfs") { // breadth-first search
        initial_board_config(game);
        
        WheelTask spinningwheel;
        std::thread th1([&]() {
            spinningwheel.run();
        });
        
        std::thread th2([&]() {
            auto solution{bfs<Board>(game.retrieve_initial_board())};
            spinningwheel.stop();
            print_solution(solution);
        });
        
        th1.join();
        th2.join();
        
    } else if (clicmd == "dfs") { // depth-first search
        initial_board_config(game);
        
        WheelTask spinningwheel;
        std::thread th1([&]() {
            spinningwheel.run();
        });
        
        std::thread th2([&]() {
            auto solution{dfs<Board>(game.retrieve_initial_board())};
            spinningwheel.stop();
            print_solution(solution);
        });
        
        th1.join();
        th2.join();
        
    } else if (clicmd == "astar") { // A* search
        initial_board_config(game);
        
        WheelTask spinningwheel;
        std::thread th1([&]() {
            spinningwheel.run();
        });
        
        std::thread th2([&]() {
            auto solution{astar<Board>(game.retrieve_initial_board(), player_heuristic)};
            spinningwheel.stop();
            print_solution(solution);
        });
        
        th1.join();
        th2.join();        
    
    } else if (clicmd == "bfs_as_astar") { // bfs as an A* search with the heuristic==0
        initial_board_config(game);
        
        WheelTask spinningwheel;
        std::thread th1([&]() {
            spinningwheel.run();
        });
        
        std::thread th2([&]() {
            auto solution{astar<Board>(game.retrieve_initial_board(), heuristic0)};
            spinningwheel.stop();
            print_solution(solution);
        });
        
        th1.join();
        th2.join();

    } else {
        std::cout << "command not recognized!\n";
    }

    return;
}