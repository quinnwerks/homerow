#include "gtest/gtest.h"
#include "parser.h"

#include <vector>

class ParserTest : public ::testing::Test {
    protected:
        Parser m_parser;
        void SetUp() override {
        }
        void TearDown() override {}
};