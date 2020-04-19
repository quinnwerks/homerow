#include "gtest/gtest.h"
#include "scanner.h"

#include <vector>



TEST(SCANNER_SHOULD, getNextWord) {
    using TEST_CASE = std::tuple<std::string, 
                                 std::pair
                                          <LANG::TOKEN, 
                                           std::string>>; 
    std::vector<TEST_CASE> cases = {{"",                  {LANG::TOKEN::END_PROG, "" }}, 
                                    {"k don't read this", {LANG::TOKEN::UP,       "k"}},
                                    {"jgarbage",          {LANG::TOKEN::DOWN,     "j"}}, 
                                    {"       a",          {LANG::TOKEN::IN,       "a"}},
                                    {"h",                 {LANG::TOKEN::LEFT,     "h"}},
                                    {"\n\n\n\n\n \ns",    {LANG::TOKEN::OUT,      "s"}}};

    std::stringstream dummy_stream;
    Scanner test_scanner(dummy_stream);
    
    for (auto& test : cases) {
        std::stringstream input_stream;

        std::string input_contents;
        std::pair<LANG::TOKEN, std::string> golden_result;
        std::tie(input_contents, golden_result) = test;

        input_stream << input_contents;
        std::pair<LANG::TOKEN, std::string> result(test_scanner.getNextWord(input_stream));
        ASSERT_EQ(result.first,  golden_result.first);
        ASSERT_EQ(result.second, golden_result.second);
    }  
}