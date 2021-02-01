#ifndef run_demo_HEADER_FILE
#define run_demo_HEADER_FILE

#include <unistd.h> // sleep
#include <utility> // pair

#include "astar.hpp"
#include "bfs.hpp"
#include "board.hpp"
#include "dfs.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include "random_walk.hpp"
#include "solution_path.hpp"
#include "threadstopper.hpp"
#include "wheeltask.hpp"

auto initial_board_config(Game&) -> void;
auto run_demo(const char*, Game&) -> void;
auto solving_status() -> void;
auto solving_wheel(const size_t&) -> void;

#endif // run_demo_HEADER_FILE