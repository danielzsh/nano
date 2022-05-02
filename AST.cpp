//
// Created by danie on 4/30/2022.
//
#include "AST.h"
template <typename T>
ASTNode<T>::~ASTNode() {

}
template <typename T>
Num<T>::Num(T value) {
    this -> value = value;
    if constexpr(std::is_same_v<T, int>) this->type = Int;
    else this->type = Double;
}
template <typename T>
T Num<T>::visit() {
    return value;
}
template <typename T1, typename T2, typename T3>
BinOp<T1, T2, T3>::BinOp(ptr<ASTNode<T1>> left, ptr<ASTNode<T2>> right, char op) {
    this->left = std::move(left);
    this->right = std::move(right);
    this->op = op;
    if (left.index() == Int && right.index() == Int) {
        this->type = Int;
    }
    else if (left.index() == String && right.index() == String) {
        this->type = String;
    }
    else if (left.index() == Double && right.index() == Double) {
        this->type = Double;
    }
    else if (left.index() == Int && right.index() == Double || right.index() == Int && left.index() == Double) {
        this->type = Double;
    }
    else {
        throw std::string("The LHS and RHS expressions are not compatible.");
    }
}
template<>
int BinOp<int, int, int>::visit() {
    if (op == '+') {
        return left->visit() + right->visit();
    }
    else if (op == '-') {
        return left->visit() - right->visit();
    }
    else if (op == '/') {
        return left->visit() / right->visit();
    }
    else if (op == '*') {
        return left->visit() * right->visit();
    }
}
void Print::visit() {
    for (auto & expr : exprs) {
        if (expr.index() == Int) {
            std::cout << GETINT(expr)->visit();
        }
        else if (expr.index() == Double) {
            // TODO: add support
        }
        else if (expr.index() == String) {
            // TODO: add support
        }
        std::cout << " ";
    }
    std::cout << '\n';
}
template <>
int Var<int>::visit() {
    return std::get<int>(st->peek()[name]);
}
//template <>
//Assign<int>::Assign(ptr<Var<int>> var, ptr<ASTNode<int>> rhs) {
//    this->var = var;
//    this->rhs = rhs;
//}
template <typename T>
void Assign<T>::visit() {
    var->st->peek()[var->name] = rhs->visit();
}
void Main::visit() {
    for (auto & statements : statements) {
        statements->visit();
    }
}
void Program::visit() {
    main->visit();
}