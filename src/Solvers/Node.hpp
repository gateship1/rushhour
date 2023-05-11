#ifndef __NODE_H__
#define __NODE_H__

#include <memory>

#include "Board.hpp"

/* Node

  data structure holding information required for a node in the A* routine

  data elements:
    board, the board the node represents
    g, the cost
    h the heuristic
    f, g + h
    parent, a pointer to the parent node for the current node
      NOTE: the initial node will have no parent and therefore be a nullptr

*/
struct Node {

    explicit Node(std::unique_ptr<Board>& board_, const std::shared_ptr<Node>& parent_=nullptr,
        const uint8_t& g_=0, const uint8_t& h_=0) noexcept :
        board( std::move(board_) ), parent( parent_ ), g( g_ ), h( h_ ), f( static_cast<uint8_t>(g_ + h_) ) {
    }
    ~Node() = default;

    std::unique_ptr<Board> board;
    const std::shared_ptr<Node> parent;
    const uint8_t g, h, f;

};

#endif // __NODE_H__
