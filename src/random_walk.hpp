#ifndef RANDOM_WALK_HEADER_FILE
#define RANDOM_WALK_HEADER_FILE

#include <cstdlib>
#include <ctime>
#include <utility> // pair

#include "solution_path.hpp"

/* random_walk
  
  generates all possible next states for a given initial state, then performs a random walk as follows:
    1) selects a random next state and add it to the path
    2) checks if random next state is a solution state, 
      if yes, a solution path has been found and the random walk is terminated
      if no, go to step 3
    3) generates all possible next states for the randomly selected state
    4) repeat steps 1 -> 3 nrandom times
    NOTE:: nrandom is hardcoded for 10 total states but could be modified in the future if desired
  
  parameters:
    state0, the initial state for the random walk
    seed_in, the supplied seed (default is NULL and the system time is used)
  
  return:
    path, the search path
    seed, the seed for the random number generator used
*/
template <typename type>
auto random_walk(const type& state0, const unsigned int* seed_in=NULL) -> std::pair<Path<type>, unsigned int> {
    
    // create a path object with the initial state as the genesis state
    auto path{Path<type>(state0)}; 
    
    // find all next possible states for the initial object
    auto next_states{state0.next()};
    
    // seed the random number generator
    unsigned int seed{};
    if (seed_in == NULL) seed = std::time(NULL);
    else seed = *seed_in;
    std::srand(seed);
    
    size_t nrandom{10};
    for (size_t i{0}; i < nrandom - 1; ++i) {
        
        // check to see if the last state in the path is the solution state 
        if (path.last_in_path().is_solution_state()) break; // stop if true (solution found)
        
        auto path_index{(std::rand() % (next_states.size()-1)) + 1}; // random path index
        
        auto move_state{next_states.at(path_index)}; // select a random state and execute a move to that state
        
        path.add_object(move_state); // add this random next state to the path
        
        next_states = path.last_in_path().next(); // repeat random walk process for next set of states
    }
    
    return std::make_pair(path, seed);
}

#endif // RANDOM_WALK_HEADER_FILE