#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "AStar.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "CmdLineDemo.hpp"
#include "heuristics.hpp"
#include "RandomWalk.hpp"
#include "SetupDefaultBoard.hpp"
#include "SetupFromCmdLine.hpp"
#include "SetupFromFile.hpp"
#include "Solver.hpp"


CmdLineDemo::CmdLineDemo(const std::vector<std::string>& args_) :
    arg_position(1), cmd_line_args(args_)  {

    if ( cmd_line_args.size() < 2 )
        throw std::out_of_range("Not enough arguments!");

}


void CmdLineDemo::run() {

    handle_args();

    if ( cmd_line_args.at(arg_position) == "astar" ) {

        std::unique_ptr<Solver> astar { std::make_unique<AStar>(starting_board, &player_heuristic_1D) };
        auto path { astar->solve() };

        if (!path.first) {
            print_solution_not_found_header(path.second);
            return;
        }
        
        print_solution_found_header(path.second);
        print_result(path.first);

    } else if ( cmd_line_args.at(arg_position) == "bfs" ) {

        std::unique_ptr<Solver> bfs { std::make_unique<BFS>(starting_board) };
        auto path { bfs->solve() };

        if (!path.first) {
            print_solution_not_found_header(path.second);
            return;
        }
        
        print_solution_found_header(path.second);
        print_result(path.first);

    } else if ( cmd_line_args.at(arg_position) == "bfs_as_astar" ) {

        std::unique_ptr<Solver> astar { std::make_unique<AStar>(starting_board, &heuristic0) };
        auto path { astar->solve() };

        if (!path.first) {
            print_solution_not_found_header(path.second);
            return;
        }
        
        print_solution_found_header(path.second);
        print_result(path.first);

    } else if ( cmd_line_args.at(arg_position) == "dfs" ) {

        std::unique_ptr<Solver> dfs { std::make_unique<DFS>(starting_board) };
        auto path { dfs->solve() };

        if (!path.first) {
            print_solution_not_found_header(path.second);
            return;
        }
        
        print_solution_found_header(path.second);
        print_result(path.first);

    } else if ( cmd_line_args.at(arg_position) == "done" ) {

        std::cout << std::boolalpha << starting_board->is_solution_state()
                  << std::noboolalpha <<  std::endl;

    } else if ( cmd_line_args.at(arg_position) == "next" ) {

        auto next_boards { std::make_unique<std::forward_list<std::unique_ptr<Board>>>(starting_board->next()) };
        print_result(next_boards, 12);

    } else if ( cmd_line_args.at(arg_position) == "print" ) {

        starting_board->print();
        std::cout << "\n" <<  std::endl;

    } else if ( cmd_line_args.at(arg_position) == "random" ) {

        std::unique_ptr<Solver> random { std::make_unique<RandomWalk>(starting_board) };
        auto path { random->solve() };
        
        print_result(path.first);

    } else {

        throw std::invalid_argument("command not recognized!");

    }

}


void CmdLineDemo::handle_args() {

    if ( cmd_line_args.at(arg_position) == "file" ) {

        arg_position++;

        if ( cmd_line_args.size() < 3 )
            throw std::out_of_range("No `file` path provided!");

        if ( cmd_line_args.size() < 4 )
            throw std::out_of_range("No command to execute on board!");

        SetupFromFile board_setup(cmd_line_args.at(arg_position));
        starting_board = board_setup.build_starting_board();

        arg_position++;

    } else if ( cmd_line_args.size() > 2 ) {

        arg_position++;

        SetupFromCmdLine board_setup(cmd_line_args.at(arg_position));
        starting_board = board_setup.build_starting_board();

        arg_position--;

    } else {

        SetupDefaultBoard board_setup;
        starting_board = board_setup.build_starting_board();

    }

}


void CmdLineDemo::print_result(std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>& path, const size_t& number_of_boards_per_row) {
    
    std::vector<std::string> board_printout_strs { };

    for (auto& board : *path )
        board_printout_strs.emplace_back( board->as_string() );

    size_t num_of_rows { 1 };
    if ( board_printout_strs.size() > number_of_boards_per_row )
        num_of_rows += (board_printout_strs.size() / number_of_boards_per_row);

    std::vector<std::string> board_super_str { };
    board_super_str.resize( num_of_rows );

    for (size_t i { 0 }; i < 8; ++i) {

        size_t row { }, board_count { };
        for (auto str : board_printout_strs) {

            board_super_str.at(row) += (str.substr(i * 8, 8) + " ");
            board_count++;
            if (board_count > (number_of_boards_per_row - 1) ) {
                board_super_str.at(row) += "\n";
                row++;
                board_count = 0;
            }

        }
        
        if ( (board_printout_strs.size() % number_of_boards_per_row) )
            board_super_str.at(row) += "\n";

    }

    for (auto entry : board_super_str)
        std::cout << entry;
    std::cout << std::endl;

}


void CmdLineDemo::print_solution_found_header(const size_t& moves) {

    std::cout << "\nSolution found!\n" << moves << " moves explored.\n";
    std::cout << "\nSolution path:\n";

}


void CmdLineDemo::print_solution_not_found_header(const size_t& moves) {

    std::cout << "\nSolution not found!\n" << moves << " moves explored.\n";

}
