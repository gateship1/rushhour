#ifndef __A_STAR_H__
#define __A_STAR_H__


#include "Node.hpp"
#include "Solver.hpp"


class AStar : public Solver {

public:

    explicit AStar(std::unique_ptr<Board>& board_, heuristic_cb heuristic_) noexcept;
    virtual ~AStar() = default;

    AStar(const AStar&) = delete;
    AStar(AStar&&) = delete;

    virtual std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> solve() override final;

};

#endif /* __A_STAR_H__ */
