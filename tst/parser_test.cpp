#include "gtest/gtest.h"
#include "parser.h"

#include <vector>
#include <tuple>

/// @brief Wrapper for parse_token.
PARSER_RET_CODE test_parse_token(Parser& test_parser, Scanner& test_scanner) {
    return test_parser.parse_token(test_scanner);
}

/// @brief Wrapper for parse.
PARSER_RET_CODE test_parse(Parser& test_parser, Scanner& test_scanner) {
    return test_parser.parse(test_scanner);
}

/// @brief Test the public interfaces of parser that are not trivial
///        getters and setters. Also tests the scanner but that is fine.
using TEST_CASE_EXPR = std::tuple<std::string, PARSER_RET_CODE>;
template<typename FUNC>
Parser run_parsing_test_case(TEST_CASE_EXPR test_case, FUNC f) {
    std::string input_string;
    PARSER_RET_CODE golden_code = PARSER_RET_CODE::FAIL;
    std::tie(input_string, golden_code) = test_case;

    std::stringstream test_stream;
    test_stream << input_string;
    Scanner test_scanner(test_stream);

    Parser test_parser;

    PARSER_RET_CODE result_code =  f(test_parser, test_scanner);
    EXPECT_EQ(golden_code, result_code);

    return test_parser;
}

/// @brief Run a test on a single expression
Parser run_parsing_test_case_expr(TEST_CASE_EXPR test_case){
    return run_parsing_test_case<PARSER_RET_CODE(*)(Parser&, Scanner&)>(test_case, test_parse_token);
}

/// @brief Run a test on a whole program.
Parser run_parsing_test_case_full(TEST_CASE_EXPR test_case){
    return run_parsing_test_case<PARSER_RET_CODE(*)(Parser&, Scanner&)>(test_case, test_parse);
}

TEST(PARSER_SHOULD, parse_mute_up) {
    run_parsing_test_case_expr({"k", PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_mute_down) {
    run_parsing_test_case_expr({"j", PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_move_left) {
    run_parsing_test_case_expr({"h", PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_move_right) {
    run_parsing_test_case_expr({"l", PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_ioop_in) {
    run_parsing_test_case_expr({"a", PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_ioop_out) {
    run_parsing_test_case_expr({"s", PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_while_okay) {
    run_parsing_test_case_expr({"F :hhh;", PARSER_RET_CODE::CONTINUE_WHILE});
}

TEST(PARSER_SHOULD, parse_while_early_eof) {
    run_parsing_test_case_expr({"F :hhh", PARSER_RET_CODE::FAIL_EARLY_EOF});
}

TEST(PARSER_SHOULD, parse_while_no_expr_begin) {
    run_parsing_test_case_expr({"Fhhh", PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN});
}

TEST(PARSER_SHOULD, parse_while_unexpected_symbol) {
    run_parsing_test_case_expr({"Fhhhy", PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_correct_passes) {
    run_parsing_test_case_expr({"F: F: hhh ; jjj ;", PARSER_RET_CODE::CONTINUE_WHILE});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_incorrect_fails_outer) {
    run_parsing_test_case_expr({"F: F: hhh ;", PARSER_RET_CODE::FAIL_EARLY_EOF});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_incorrect_fails_inner) {
    run_parsing_test_case_expr({"F: F: hhh y ; hh;", PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL});
}

using TEST_CASE_PARSER_STATE = std::tuple<std::string, ParserState> ;
void test_parser_state(TEST_CASE_PARSER_STATE test_case) {
    std::string input_text;
    ParserState golden_state;
    std::tie(input_text, golden_state) = test_case;
    TEST_CASE_EXPR parse_target = {input_text, PARSER_RET_CODE::ACCEPT};
    Parser test_parser = run_parsing_test_case_full(parse_target);
    ParserState result_state = test_parser.getState();
    EXPECT_EQ(golden_state.curr_cell, result_state.curr_cell);
}

TEST(PARSER_SHOULD, mutate_parser_state_no_displacement) {
    ParserState test_state(1);
    test_parser_state({"hhlll", test_state});
}

TEST(PARSER_SHOULD, mutate_parser_state_right_displacement) {
    ParserState test_state(2);
    test_parser_state({"hlhlhlll", test_state});
}

TEST(PARSER_SHOULD, mutate_parser_state_left_displacement) {
    ParserState test_state(-6);
    test_parser_state({"hlhlhhhhhh", test_state});
}

using TEST_CASE_PARSER_AST = std::tuple<std::string, std::string> ;
void test_parser_state(TEST_CASE_PARSER_AST test_case) {
    std::string input_text;
    std::string golden_tree;
    std::tie(input_text, golden_tree) = test_case;
    TEST_CASE_EXPR parse_target = {input_text, PARSER_RET_CODE::ACCEPT};
    Parser test_parser = run_parsing_test_case_full(parse_target);
    std::string result_tree = (test_parser.getAst()).get_debug_tree();
    EXPECT_EQ(golden_tree, result_tree);
}

TEST(PARSER_SHOULD, apply_diff_ops_same_cell) {
    std::string golden_tree("TYPE:0\n"
                            "  |-TYPE:3-REG:0-VAL:-1\n"
                            "  `-TYPE:3-REG:0-VAL:1\n");
    test_parser_state({"jk", golden_tree});
}

TEST(PARSER_SHOULD, apply_same_ops_diff_cell) {
    std::string golden_tree("TYPE:0\n"
                            "  |-TYPE:2-REG:-1-VAL:-1\n"
                            "  |-TYPE:2-REG:0-VAL:1\n"
                            "  `-TYPE:2-REG:1-VAL:1\n");
    test_parser_state({"hll", golden_tree});
}

TEST(PARSER_SHOULD, set_curr_node_properly) {
    std::string golden_tree("TYPE:0\n"
                            "  |-TYPE:1\n"
                            "  | |-TYPE:3-REG:0-VAL:-1\n"
                            "  | |-TYPE:1\n"
                            "  | | `-TYPE:3-REG:0-VAL:1\n"
                            "  | `-TYPE:2-REG:1-VAL:1\n"
                            "  `-TYPE:2-REG:0-VAL:-1\n");
    test_parser_state({"F: j F: k; l; h", golden_tree});
}