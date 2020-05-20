#ifndef IR_C_H
#define IR_C_H

class IrToC {
    public:
        std::string getOutput(const Ast& ast);
    private:
        std::string getExprString(const ExprNode& node);
        std::string getBinaryString(const BinaryNode& node);
};

#endif