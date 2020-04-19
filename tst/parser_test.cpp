#include "gtest/gtest.h"
#include "parser.h"

#include <vector>
#include <tuple>

TOKEN_PAIR test_pair(TOKEN token) {
    return std::make_pair(token, "");
}


using TEST_CASE = std::tuple<TOKEN_PAIR, PARSER_RET_CODE>;
void run_test_case(TEST_CASE test_case) {
    TOKEN_PAIR input_token;
    PARSER_RET_CODE golden_code = PARSER_RET_CODE::FAIL;
    std::tie(input_token, golden_code) = test_case;

    std::stringstream test_stream;
    Scanner scanner(test_stream);

    Parser test_parser;

    auto result_code =  test_parser.parse_token(scanner, input_token);
    ASSERT_EQ(golden_code, result_code);
}


TEST(PARSER_SHOULD, parse_mute_up) {
    run_test_case({test_pair(TOKEN::UP), PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_mute_down) {
    run_test_case({test_pair(TOKEN::DOWN), PARSER_RET_CODE::CONTINUE_MUTE});
}

TEST(PARSER_SHOULD, parse_move_left) {
    run_test_case({test_pair(TOKEN::LEFT), PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_move_right) {
    run_test_case({test_pair(TOKEN::RIGHT), PARSER_RET_CODE::CONTINUE_MOVE});
}

TEST(PARSER_SHOULD, parse_ioop_in) {
    run_test_case({test_pair(TOKEN::IN), PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_ioop_out) {
    run_test_case({test_pair(TOKEN::OUT), PARSER_RET_CODE::CONTINUE_IOOP});
}

TEST(PARSER_SHOULD, parse_while_out) {
    run_test_case({test_pair(TOKEN::WHILE), PARSER_RET_CODE::CONTINUE_WHILE});
}