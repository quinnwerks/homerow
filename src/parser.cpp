#include "parser.h"

Parser::Parser() {

}

Parser::Parser(Parser& copy_this) {
    *this = copy_this;
}

Parser& Parser::operator=(Parser& copy_this) {
    if(this != &copy_this) {

    }
    return *this;    
}

bool Parser::processWord(TOKEN_PAIR word) {
    return false;
}

std::string Parser::dumpRepresentation() {
    return "";
}