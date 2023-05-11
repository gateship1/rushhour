#ifndef __CMD_LINE_DEMO_H__
#define __CMD_LINE_DEMO_H__

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Board.hpp"
#include "Node.hpp"


class CmdLineDemo {

public:

    CmdLineDemo(const std::vector<std::string>& args);
    ~CmdLineDemo() = default;

    CmdLineDemo(const CmdLineDemo&) = delete;
    CmdLineDemo(CmdLineDemo&&) = delete;

    void run();

private:

   void handle_args();
   void print_result(std::unique_ptr<std::forward_list<std::unique_ptr<Board>>>& path,
       const size_t& number_of_boards_per_row=6);
   void print_solution_found_header(const size_t& moves);
   void print_solution_not_found_header(const size_t& moves);

   uint8_t arg_position;
   const std::vector<std::string> cmd_line_args;
   std::unique_ptr<Board> starting_board;



};

#endif /* __CMD_LINE_DEMO_H__ */
