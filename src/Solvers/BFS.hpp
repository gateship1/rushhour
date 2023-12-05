#ifndef __BFS_H__
#define __BFS_H__


#include "Node.hpp"
#include "Solver.hpp"


class BFS : public Solver {

public:

    explicit BFS(std::unique_ptr<Board>& board_) noexcept;
    virtual ~BFS() = default;

    BFS(const BFS&) = delete;
    BFS(BFS&&) = delete;
    BFS& operator=(const BFS&) = delete;
    BFS& operator=(BFS&&) = delete;

    virtual std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> solve() override final;

};


#endif /* __BFS_H__ */
