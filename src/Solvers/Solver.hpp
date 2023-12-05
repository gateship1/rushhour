#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <list>
#include <memory>

#include "Board.hpp"
#include "heuristics.hpp"
#include "Node.hpp"


class Solver {

public:

    explicit Solver(std::unique_ptr<Board>& board_, heuristic_cb heuristic_ = nullptr) noexcept;
    virtual ~Solver() = default;

    Solver(const Solver&) = delete;
    Solver(Solver&&) = delete;
    Solver& operator=(const Solver&) = delete;
    Solver& operator=(Solver&&) = delete;

    virtual std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> solve() = 0;

protected:

    std::unique_ptr<std::forward_list<std::unique_ptr<Board>>> build_solution_path(std::shared_ptr<Node>& node_on_path);

    heuristic_cb heuristic;
    size_t moves_explored;

    std::shared_ptr<Node> starting_node;

};

#endif /* __SOLVER_H__ */
