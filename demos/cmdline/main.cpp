#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "CmdLineDemo.hpp"


std::vector<std::string> cmd_line_args_to_str(const int& argc, char ** argv);


int main(int argc, char * argv[]) {

    auto args { cmd_line_args_to_str(argc, argv) };

    try {

        CmdLineDemo demo(args);
        demo.run();

    } catch(const std::exception& e) {

        std::cerr << "\nError: " << e.what() << std::endl;

    }

    return 0;
}


std::vector<std::string> cmd_line_args_to_str(const int& argc, char ** argv) {

    std::vector<std::string> args;

    for (uint8_t i { }; i < argc; ++i)
        args.emplace_back(static_cast<std::string>(argv[i]));

    return args;

}
