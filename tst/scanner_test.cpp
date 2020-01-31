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
    std::vector<std::string> cases = {"", 
                                      "ssss", 
                                      " aaaaa bbbbbb ", 
                                      " skl   "};

    for (auto& test : cases) {
        std::stringstream input_stream;
        input_stream << test;
        std::string word(m_scanner.getNextWord(input_stream));
        std::cout << word << std::endl;
    }  
}