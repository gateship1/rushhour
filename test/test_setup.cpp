#include <array>
#include <filesystem>
#include <exception>
#include <fstream>
#include <string>
#include <sstream>

#include "UnitTest.hpp"

#include "SetupDefaultBoard.hpp"
#include "SetupFromCmdLine.hpp"
#include "SetupFromFile.hpp"


TEST_F(UnitTest, default_setup) {

    SetupDefaultBoard default_board_setup;
    std::unique_ptr<Board> default_board { default_board_setup.build_starting_board() };

    initialize_default_board();

    ASSERT_EQ( default_board->get_state(), game_board->get_state() );

}


TEST_F(UnitTest, setup_from_cmd_line) {

    SetupFromCmdLine board_setup("aabbco|d eeco|dfpxxo| fpqqq|  p   |hh    ");
    std::unique_ptr<Board> board { board_setup.build_starting_board() };

    initialize_sample_board3();

    ASSERT_EQ( board->get_state(), game_board->get_state() );

}


TEST_F(UnitTest, setup_from_cmd_line_no_player_vehicle) {

    SetupFromCmdLine board_setup("aabbco|d eeco|dfp  o| fpqqq|  p   |hh    ");
    std::string expected_error_printout { "Error: board does not have a player vehicle!" };

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {

        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        std::string text { buffer.str() };
        auto result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(result);

    }

}


TEST_F(UnitTest, setup_from_cmd_line_empty_board) {

    SetupFromCmdLine board_setup("      |      |      |      |      |      ");
    std::string expected_error_printout { "Error: board is empty!" };

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {

        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        std::string text { buffer.str() };
        auto result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(result);

    }

}


TEST_F(UnitTest, setup_from_cmd_line_malformed_board) {

    SetupFromCmdLine board_setup("aabbco|d eeco|dfpxxo| fpqqq|  p  |hh    ");
    std::string expected_error_printout { "Error: Malformed board string!" };

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {
        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        std::string text { buffer.str() };
        auto result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(result);

    }

}


TEST_F(UnitTest, setup_from_file) {

    std::array<std::string, 6> lines {
        "  o aa",
        "  o   ",
        "xxo   ",
        "ppp  q",
        "     q",
        "     q"
    };
    std::string filename { "test.txt" };
    std::string expected_printout { "Reading => " + filename + "\nInput read." };

    try {
        std::ofstream input_file{filename, std::ios::out};
        for (auto line : lines) {
            input_file << line << "\n";
        }
        input_file.close();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    SetupFromFile board_setup(filename);
    std::unique_ptr<Board> default_board { board_setup.build_starting_board() };

    std::string text { buffer.str() };
    auto result { text.compare(expected_printout) };

    std::cout.rdbuf(prevcoutbuf);
    ASSERT_TRUE(result);

    initialize_default_board();

    ASSERT_EQ( default_board->get_state(), game_board->get_state() );

    std::filesystem::remove(filename);

}


TEST_F(UnitTest, setup_from_file_no_player_vehicle) {

    std::array<std::string, 6> lines {
        "  o aa",
        "  o   ",
        "bbo   ",
        "ppp  q",
        "     q",
        "     q"
    };
    std::string filename { "test.txt" };
    std::string expected_printout { "Reading => " + filename + "\nInput read." };
    std::string expected_error_printout { "Error: board does not have a player vehicle!" };

    try {
        std::ofstream input_file{filename, std::ios::out};
        for (auto line : lines) {
            input_file << line << "\n";
        }
        input_file.close();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    SetupFromFile board_setup(filename);

    std::string text { buffer.str() };
    auto result { text.compare(expected_printout) };

    std::cout.rdbuf(prevcoutbuf);
    ASSERT_TRUE(result);

    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {
        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        text = buffer.str();
        auto error_result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(error_result);

    }

    std::filesystem::remove(filename);

}


TEST_F(UnitTest, setup_from_file_board_is_empty) {

    std::array<std::string, 6> lines {
        "      ",
        "      ",
        "      ",
        "      ",
        "      ",
        "      "
    };
    std::string filename { "test.txt" };
    std::string expected_printout { "Reading => " + filename + "\nInput read." };
    std::string expected_error_printout { "Error: board is empty!" };

    try {
        std::ofstream input_file{filename, std::ios::out};
        for (auto line : lines) {
            input_file << line << "\n";
        }
        input_file.close();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    SetupFromFile board_setup(filename);

    std::string text { buffer.str() };
    auto result { text.compare(expected_printout) };

    std::cout.rdbuf(prevcoutbuf);
    ASSERT_TRUE(result);

    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {
        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        text = buffer.str();
        auto error_result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(error_result);

    }

    std::filesystem::remove(filename);

}


TEST_F(UnitTest, setup_from_file_malformed_board) {

    std::array<std::string, 6> lines {
        "  o aa",
        "  o    ",
        "xxo   ",
        "ppp  q",
        "     q",
        "     q"
    };
    std::string filename { "malformed.txt" };
    std::string expected_printout { "Reading => " + filename + "\nInput read." };
    std::string expected_error_printout { "Error: Malformed board string!" };

    try {
        std::ofstream input_file{filename, std::ios::out};
        for (auto line : lines) {
            input_file << line << "\n";
        }
        input_file.close();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    SetupFromFile board_setup(filename);

    std::string text { buffer.str() };
    auto result { text.compare(expected_printout) };

    std::cout.rdbuf(prevcoutbuf);
    ASSERT_TRUE(result);

    prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    try {

        std::unique_ptr<Board> test_board { board_setup.build_starting_board() };

    } catch(...) {

        text = buffer.str();
        auto error_result { text.compare(expected_error_printout) };
        std::cout.rdbuf(prevcoutbuf);
        ASSERT_TRUE(error_result);
    }

    std::filesystem::remove(filename);

}
