#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <stack>

#include "RandomWalk.hpp"
#include "defines.hpp"
#include "Node.hpp"


RandomWalk::RandomWalk(std::unique_ptr<Board>& board_, const uint16_t& moves_,
    const std::unique_ptr<unsigned int>& seed_) noexcept :
    Solver( board_ ), moves(moves_) {

    (seed_ == nullptr) ? seed = static_cast<unsigned int>( std::time(nullptr) ) : seed = *seed_;
    std::srand(seed);

    std::cout << "\nSeed for random walk: " << seed << std::endl;

}


/* random walk

  performs a random walk for `moves` moves (unless a solution is found before `moves` is reached)

  generates all possible next states for a given initial state, then performs a random walk as follows:
    1) selects a random next state and add it to the path
    2) checks if random next state is a solution state, 
      if yes, a solution path has been found and the random walk is terminated
      if no, go to step 3
    3) generates all possible next states for the randomly selected state
    4) repeat steps 1 -> 3 `moves` times

*/
std::pair<std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>, size_t> RandomWalk::solve() {

    std::stack<std::shared_ptr<Node>> stk { };
    stk.push(starting_node);

    for (uint16_t i { }; i < moves; ++i) {
        
        // check to see if the last state in the path is the solution state 
        if (stk.top()->board->is_solution_state()) break; // stop if true (solution found)

        auto next_states { stk.top()->board->next() };

        moves_explored++;

        auto path_index{ (std::rand() % ( distance( next_states.begin(),
            next_states.end() ) -1 ) ) + 1 }; // random path index

        for (long index { }; index < path_index; ++index)
            next_states.pop_front();

        auto move_state { std::move( next_states.front() ) }; // select a random state and execute a move to that state

        stk.push(std::make_shared<Node>(move_state, stk.top()));

    }

    return std::make_pair( build_solution_path(stk.top()), moves_explored);

}
