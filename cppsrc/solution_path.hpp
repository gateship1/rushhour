#ifndef SOLUTION_PATH_HEADER_FILE
#define SOLUTION_PATH_HEADER_FILE

#include <iostream>
#include <memory> // make_shared, shared_ptr
#include <queue>  // deque, priority_queue
#include <vector>

#include "node.hpp"

template <typename type>
struct Path {
    
    Path(const type&);
    Path(const std::shared_ptr<Node<type>>);
    Path(const std::vector<type>&);
    
    // methods
    auto add_object(const type&) -> void;
    auto build_path(const std::shared_ptr<Node<type>>) -> void;
    auto last_in_path() const -> type;
    
    // data members
    std::vector<type> path_objects;
    
};

/* Path constructor
  
  creates a new potential solution path (set of object states)
  
  parameters:
    object, the initial object state for a game
*/
template <typename type>
Path<type>::Path(const type& object) {
    this->add_object(object);
}

/* Path constructor
  
  creates a new potential solution path (set of nodes)
  
  parameters:
    node0, the solution state node for the path
*/
template <typename type>
Path<type>::Path(const std::shared_ptr<Node<type>> node0) {
    this->build_path(node0);
}

/* Path constructor
  
  creates a new potential solution path (set of object states)
  
  parameters:
    objects, the initial object states for a game
*/
template <typename type>
Path<type>::Path(const std::vector<type>& objects) : path_objects(objects) {
}

/* add_object
  
  add an object of type type to the current path object
  
  parameters:
    object to add to the path
*/
template <typename type>
auto Path<type>::add_object(const type& object) -> void {
    this->path_objects.push_back(object);
    return;
}

/* build_path
  
  build the solution path from the solution state node back to the starting node

  parameters:
    node0, the solution state node
*/
template <typename type>
auto Path<type>::build_path(const std::shared_ptr<Node<type>> node0) -> void {
    
    std::deque<type> solution_states{}; // double ended queue of solution states (allows front pushing)
    auto node{node0}; // initialize a node as the solution state
    while (node->parent != nullptr) { // build the path of states from a linked list of nodes until the initial state is reached
        solution_states.push_front(node->state); // add the node state to the solution state double ended queue
        node = node->parent; // set the pointer for the node to the its parent
    }
    solution_states.push_front(node->state); // add the initial state to the double ended queue
    // create a path object with the list of states leading to the solution
    this->path_objects = {solution_states.begin(), solution_states.end()};
    return;
}

/* last_in_path
  
  retrieve the last object of type type in the current path object
  
  return:
    last object in the path
*/
template <typename type>
auto Path<type>::last_in_path() const -> type {
    return this->path_objects.back();
}

#endif // SOLUTION_PATH_HEADER_FILE