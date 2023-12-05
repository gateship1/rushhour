#ifndef __RANDOM_WALK_H__
#define __RANDOM_WALK_H__


#include "Node.hpp"
#include "Solver.hpp"


class RandomWalk : public Solver {

public:

    explicit RandomWalk(std::unique_ptr<Board>& board_, const uint16_t& moves_=10,
        const std::unique_ptr<unsigned int>& seed_=nullptr ) noexcept;
    virtual ~RandomWalk() = default;

    RandomWalk(const RandomWalk&) = delete;
    RandomWalk(RandomWalk&&) = delete;
    RandomWalk& operator=(const RandomWalk&) = delete;
    RandomWalk& operator=(RandomWalk&&) = delete;

    virtual std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> solve() override final;

private:

    const uint16_t moves;
    unsigned int seed;

};

#endif /* __RANDOM_WALK_H__ */
