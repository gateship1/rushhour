#ifndef NODE_HEADER_FILE
#define NODE_HEADER_FILE

/* Node
  
  data structure holding information required for a node in the A* routine

  data elements:
    state, the state the node represents
    g, the cost
    h the heuristic
    f, g + h
    parent, a pointer to the parent node for the current node
      NOTE: the initial node will have no parent and therefore be a nullptr
    signature, a string representation (in hex) of the node state - used for checking if the node is visited or not
*/
template <typename type>
struct Node {
    
    Node(const type& state_, std::shared_ptr<Node<type>> parent_, const size_t& g_=0, const size_t& h_=0) :
        state(state_), parent(parent_), g(g_), h(h_), f(g_ + h_), signature(state_.get_signature()) {
    }
    
    const type state;
    const std::shared_ptr<Node<type>> parent;
    const size_t g, h, f;
    const std::string signature;
};

#endif // NODE_HEADER_FILE