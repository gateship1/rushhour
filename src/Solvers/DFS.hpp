#ifndef __DFS_H__
#define __DFS_H__


#include "Node.hpp"
#include "Solver.hpp"

class DFS : public Solver {

public:

    explicit DFS(std::unique_ptr<Board>& board_) noexcept;
    virtual ~DFS() = default;

    DFS(const DFS&) = delete;
    DFS(DFS&&) = delete;
    DFS& operator=(const DFS&) = delete;
    DFS& operator=(DFS&&) = delete;

    virtual std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> solve() override final;

};


#endif /* __DFS_H__ */
