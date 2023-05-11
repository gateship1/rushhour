#include <algorithm>
#include <stack>
#include <vector>

#include "DFS.hpp"
#include "defines.hpp"
#include "Node.hpp"


DFS::DFS(std::unique_ptr<Board>& board_) noexcept :
    Solver( board_ ) {

}


/* dfs
  
  performs a depth-first search for the solution state (if it exists)

*/
std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> DFS::solve() {

    // set up a stack of state sets (paths)
    std::stack<std::shared_ptr<Node>> stk { };
    stk.push(starting_node);

    // set up a list of nodes that have been "visited"
    std::vector<uint64_t> visited { starting_node->board->get_state() };

    while( !stk.empty() ) {

        auto current_node{ stk.top() };
        stk.pop(); // remove current node from the stack

        // check the current node for a solution state
        if ( current_node->board->is_solution_state() ) {
            return std::make_pair( build_solution_path(current_node), moves_explored); // return the solution
        }

        // add the signature for the current node to the list of visited states
        visited.emplace_back( current_node->board->get_state() );

        for ( auto& next_state : current_node->board->next() ) {

            if ( !(std::find( visited.begin(), visited.end(), next_state->get_state() ) != visited.end() ) ) {

                visited.emplace_back( next_state->get_state() );
                auto new_node {
                    std::make_shared<Node>(next_state, current_node, current_node->g + 1) };
                stk.emplace(new_node); // put the new path on the stack

            }

        }

        moves_explored++;
    }

    // a solution could not be found (or does not exist)
    return std::make_pair(nullptr, moves_explored);

}
