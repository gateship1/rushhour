#include "Solver.hpp"

Solver::Solver(std::unique_ptr<Board>& board_, heuristic_cb heuristic_) noexcept :
    heuristic(heuristic_), moves_explored( 0 ) {

    auto starting_board { std::move(board_) };
    if (heuristic) {
        auto h { starting_board->get_state() };
        starting_node = std::make_shared<Node>(starting_board, nullptr, 0, h);
    } else {
        starting_node = std::make_shared<Node>(starting_board);
    }

}


std::unique_ptr<std::forward_list<std::unique_ptr<Board>>> Solver::build_solution_path(std::shared_ptr<Node>& node_on_path) {

    auto solution_path { std::make_unique<std::forward_list<std::unique_ptr<Board>>>() };

    while ( node_on_path ) {

        solution_path->push_front( std::move(node_on_path->board) );
        node_on_path = node_on_path->parent;

    }

    return solution_path;

}
