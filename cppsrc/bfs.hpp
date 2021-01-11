#ifndef BFS_HEADER_FILE
#define BFS_HEADER_FILE

#include <algorithm> // find
#include <queue> // queue
#include <utility> // pair

#include "node.hpp"
#include "solution_path.hpp"

/* bfs
  
  performs a breadth-first search for the solution state (if it exists)
  
  parameters:
    state0, the initial state to start the breadth-first search
  
  return:
    path, the solution path (path is empty if solution does not exist)
    moves_explored, the number of moves explored to find (or fail to find) a solution state
*/
template <typename type>
auto bfs(const type& state0) -> std::pair<Path<type>, size_t> {
    
    size_t moves_explored{0}; // initialize the number of moves explored
    
    // create initial node based on input state (initial state)
    auto start = std::make_shared<Node<type>>(state0, nullptr);
    
    // set up a queue of nodes to explore
    std::queue<std::shared_ptr<Node<type>>> nqueue;
    nqueue.push(start); // add the initial node to priority queue
    
    // set up a list of nodes that have been "visited"
    std::vector<std::string> visited{};   
    
    while(!nqueue.empty()) {
        
        auto current_node{nqueue.front()};
        nqueue.pop(); // remove current node from the queue
        
        // check the current node for a solution state
        if (current_node->state.is_solution_state()) { // if a solution state has been found
            Path<type> path(current_node);
            return std::make_pair(path, moves_explored);
        }
        
        // add the signature for the current node to the list of visited states
        visited.emplace_back(current_node->state.get_signature());

        for (const auto& next_state : current_node->state.next()) {
            if (!(std::find(visited.begin(), visited.end(), next_state.get_signature()) != visited.end())) {
                auto new_node = std::make_shared<Node<type>>(next_state, current_node, current_node->g + 1);
                nqueue.emplace(new_node); // put the new path on the queue
                visited.emplace_back(next_state.get_signature());
            }
        }
        
        // increment the number of moves explored
        moves_explored++;
    }
    
    // a solution could not be found (or does not exist)
    Path<type> path(state0); // create a dummy path with the initial state then clear it
    path.path_objects.clear();
    return std::make_pair(path, moves_explored);
}

#endif // BFS_HEADER_FILE