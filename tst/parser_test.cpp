#include "gtest/gtest.h"
#include "parser.h"

#include <vector>
#include <tuple>

using TEST_CASE_EXPR = std::tuple<std::string, PARSER_RET_CODE>;
void run_test_case_expr(TEST_CASE_EXPR test_case) {
    std::string input_string;
    PARSER_RET_CODE golden_code = PARSER_RET_CODE::FAIL;
    std::tie(input_string, golden_code) = test_case;

    std::stringstream test_stream;
    test_stream << input_string;
    Scanner scanner(test_stream);

    Parser test_parser;
    auto result_code =  test_parser.parse_token(scanner);
    ASSERT_EQ(golden_code, result_code);
}


TEST(PARSER_SHOULD, parse_mute_up) {
    run_test_case_expr({"k", PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_mute_down) {
    run_test_case_expr({"j", PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_move_left) {
    run_test_case_expr({"h", PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_move_right) {
    run_test_case_expr({"l", PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_ioop_in) {
    run_test_case_expr({"a", PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_ioop_out) {
    run_test_case_expr({"s", PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_while_okay) {
    run_test_case_expr({"F :hhh;", PARSER_RET_CODE::CONTINUE_WHILE});
}

TEST(PARSER_SHOULD, parse_while_early_eof) {
    run_test_case_expr({"F :hhh", PARSER_RET_CODE::FAIL_EARLY_EOF});
}

TEST(PARSER_SHOULD, parse_while_no_expr_begin) {
    run_test_case_expr({"Fhhh", PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN});
}

TEST(PARSER_SHOULD, parse_while_unexpected_symbol) {
    run_test_case_expr({"Fhhhy", PARSER_RET_CODE::FAIL_NO_EXPR_BEGIN});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_correct_passes) {
    run_test_case_expr({"F: F: hhh ; jjj ;", PARSER_RET_CODE::CONTINUE_WHILE});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_incorrect_fails_outer) {
    run_test_case_expr({"F: F: hhh ;", PARSER_RET_CODE::FAIL_EARLY_EOF});
}

TEST(PARSER_SHOULD, parse_while_embedded_whiles_incorrect_fails_inner) {
    run_test_case_expr({"F: F: hhh y ; hh;", PARSER_RET_CODE::FAIL_UNEXPECTED_SYMBOL});
}