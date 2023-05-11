#include <algorithm>
#include <queue>
#include <vector>

#include "BFS.hpp"
#include "defines.hpp"
#include "Node.hpp"


BFS::BFS(std::unique_ptr<Board>& board_) noexcept :
    Solver( board_ ) {

}


/* bfs
  
  performs a breadth-first search for the solution state (if it exists)

*/
std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> BFS::solve() {

    // set up a queue of nodes to explore
    std::queue<std::shared_ptr<Node>> nqueue;
    nqueue.push(starting_node); // add the initial node to priority queue

    // set up a list of nodes that have been "visited"
    std::vector<uint64_t> visited { starting_node->board->get_state() };

    while( !nqueue.empty() ) {

        auto current_node{ nqueue.front() };
        nqueue.pop(); // remove current node from the queue

        // check the current node for a solution state
        if ( current_node->board->is_solution_state() ) {
            return std::make_pair( build_solution_path(current_node), moves_explored); // return the solution
        }

        // add the signature for the current node to the list of visited states
        visited.emplace_back( current_node->board->get_state() );

        for ( auto& next_state : current_node->board->next() ) {

            if ( !( std::find(visited.begin(), visited.end(), next_state->get_state() ) != visited.end() ) ) {

                visited.emplace_back( next_state->get_state() );
                auto new_node {
                    std::make_shared<Node>(next_state, current_node, current_node->g + 1) };
                nqueue.emplace(new_node); // put the new path on the queue

            }

        }

        // increment the number of moves explored
        moves_explored++;

    }

    // a solution could not be found (or does not exist)
    return std::make_pair(nullptr, moves_explored);

}
