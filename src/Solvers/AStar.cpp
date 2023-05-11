#include <algorithm>
#include <queue>

#include "AStar.hpp"
#include "defines.hpp"
#include "heuristics.hpp"
#include "Node.hpp"


AStar::AStar(std::unique_ptr<Board>& board_, heuristic_cb heuristic_) noexcept :
    Solver( board_, heuristic_ ) {

}


/* astar

  performs an A* search for the solution state (if it exists)

*/
std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> AStar::solve() {

    // custom comparator to build the special value priority queue (lowest 'f' value gets priority)
    const auto& cmp =
        [](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node> rhs) {
            return lhs->f > rhs->f;
        };

    // set up a special value priority queue - priority is given to the node with the smallest 'f' value
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(cmp)> open_nodes(cmp);
    open_nodes.push( starting_node ); // add the initial node to priority queue

    // create a list of nodes that have been visited (closed)
    // note only the signature (hash) of these nodes is stored in the list
    std::vector<uint64_t> closed_nodes { starting_node->board->get_state() };

    // A* algorithm - continue search for solution state as long as the open list contains unvisited nodes
    while( !open_nodes.empty() ) {

        // current node being inspected for a solution state
        auto current_node { open_nodes.top()}; // node in the special value priority queue with the smallest 'f' value
        open_nodes.pop(); // remove current node from open

        // check the current node for a solution state
        if ( current_node->board->is_solution_state() ) {
            return std::make_pair( build_solution_path(current_node), moves_explored); // return the solution
        }

        // add the signature for the current node to the list of closed states
        closed_nodes.emplace_back( current_node->board->get_state() );

        // add all the possible next states from the current node to the priority queue (they are sorted upon addition by lowest f)
        for ( auto& next_state : current_node->board->next() ) {

            if ( !( std::find( closed_nodes.begin(), closed_nodes.end(), next_state->get_state() ) != closed_nodes.end() ) ) {

                closed_nodes.emplace_back( next_state->get_state() );
                auto new_node { 
                    std::make_shared<Node>( next_state, current_node, current_node->g + 1, heuristic(next_state) ) };
                open_nodes.push( new_node );

            }

        }
        
        // increment the number of moves explored
        moves_explored++;

    }

    // a solution could not be found (or does not exist)
    return std::make_pair(nullptr, moves_explored);

}
