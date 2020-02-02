#include "gtest/gtest.h"
#include "scanner.h"

#include <vector>


class ScannerTest : public ::testing::Test {
    protected:
        Scanner m_scanner;
        void SetUp() override {
            m_scanner = Scanner();
        }
        void TearDown() override {}
};

TEST_F(ScannerTest, getNextWord) {
    using TEST_CASE = std::tuple<std::string, 
                                 std::pair
                                          <LANG::TOKEN, 
                                           std::string>>; 
    std::vector<TEST_CASE> cases = {{"",                  {LANG::TOKEN::END_FILE, "" }}, 
                                    {"k don't read this", {LANG::TOKEN::UP,       "k"}},
                                    {"jgarbage",          {LANG::TOKEN::DOWN,     "j"}}, 
                                    {"       a",          {LANG::TOKEN::IN,       "a"}},
                                    {"\n\n\n\n\n \ns",    {LANG::TOKEN::OUT,      "s"}}};

    for (auto& test : cases) {
        std::stringstream input_stream;

        std::string input_contents;
        std::pair<LANG::TOKEN, std::string> golden_result;
        std::tie(input_contents, golden_result) = test;

        input_stream << input_contents;
        std::pair<LANG::TOKEN, std::string> result(m_scanner.getNextWord(input_stream));
        ASSERT_EQ(result.first,  golden_result.first);
        ASSERT_EQ(result.second, golden_result.second);
    }  
}