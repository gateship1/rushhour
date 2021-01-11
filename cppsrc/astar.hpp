#ifndef ASTAR_HEADER_FILE
#define ASTAR_HEADER_FILE

#include <iostream>
#include <memory> // make_shared, shared_ptr
#include <queue> // deque, priority_queue
#include <utility> // pair
#include <vector>

#include "heuristics.hpp"
#include "node.hpp"
#include "solution_path.hpp"

/* astar
  
  performs an A* search for the solution state (if it exists)
  
  parameters:
    state0, the initial state from which to begin the A* search
    heuristic, the heuristic function to use in the A* search
  
  return,
    the path to the solution state from the input state (empty if a path cannot be found)
    the number of moves explored to reach (or fail to reach) the solution state
*/
template <typename type, typename func>
auto astar(const type& state0, func heuristic) -> std::pair<Path<type>, size_t> {
    
    size_t moves_explored{0}; // initialize the number of moves explored
    
    // create initial node based on input state (initial state)
    auto start = std::make_shared<Node<type>>(state0, nullptr, 0, heuristic(state0));

    // custom comparator to build the special value priority queue (lowest 'f' value gets priority)
    const auto& cmp = [](const std::shared_ptr<Node<type>> lhs, const std::shared_ptr<Node<type>> rhs) {
        return lhs->f > rhs->f;
    };
    // set up a special value priority queue - priority is given to the node with the smallest 'f' value
    std::priority_queue<std::shared_ptr<Node<type>>, std::vector<std::shared_ptr<Node<type>>>, decltype(cmp)> open_(cmp);
    open_.push(start); // add the initial node to priority queue
    
    // create a list of nodes that have been visited (closed)
    // note only the signature (hash) of these nodes is stored in the list
    std::vector<std::string> closed_{state0.get_signature()};
    
    // A* algorithm - continue search for solution state as long as the open list contains unvisited nodes
    while(!open_.empty()) {
        
        // current node being inspected for a solution state
        auto current_node{open_.top()}; // node in the special value priority queue with the smallest 'f' value
        open_.pop(); // remove current node from open
        
        // check the current node for a solution state
        if (current_node->state.is_solution_state()) { // if a solution state has been found
            Path<type> path(current_node);
            return std::make_pair(path, moves_explored); // return the solution path and the number of moves explored to find it
        }
        
        // add the signature for the current node to the list of closed states
        closed_.emplace_back(current_node->state.get_signature());
        
        // add all the possible next states from the current node to the priority queue (they are sorted upon addition by lowest f)
        for (const auto& next_state : current_node->state.next()) {
            if (!(std::find(closed_.begin(), closed_.end(), next_state.get_signature()) != closed_.end())) {
                auto new_node = std::make_shared<Node<type>>(next_state, current_node, current_node->g + 1, heuristic(next_state));
                open_.push(new_node);
                closed_.emplace_back(next_state.get_signature());
            }
        }
        
        // increment the number of moves explored
        moves_explored++;
    }
    
    // a solution could not be found (or does not exist)
    Path<type> path(state0); // create a dummy path with the initial state then clear it
    path.path_objects.clear();
    return std::make_pair(path, moves_explored); // return an empty solution path with the number of moves explored
}

#endif // ASTAR_HEADER_FILE