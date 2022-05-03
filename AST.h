//
// Created by danie on 4/30/2022.
//

#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "Stack.h"
#define GETINT(PTR) std::get<ptr<ASTNode<int>>>(PTR)
#define ISTYPE(T1, T2) std::is_same_v<T1, T2>
enum Type {
    Int = 0,
    Double = 1,
    String = 2,
    Void = 3
};
template <typename T>
using ptr = std::unique_ptr<T>;
// abstract base class for all nodes
template <typename T>
class ASTNode {
public:
    Type type = Void;
    // process a node
    virtual T visit() = 0;
    virtual ~ASTNode() = 0;
};
template <typename T>
ASTNode<T>::~ASTNode() = default;
using node = std::variant<ptr<ASTNode<int>>, ptr<ASTNode<double>>, ptr<ASTNode<std::string>>>;
template <typename T>
class Num : public ASTNode<T> {
public:
    T value;
    Num(T value) {
        this -> value = value;
        if constexpr(std::is_same_v<T, int>) this->type = Int;
        else this->type = Double;
    }
    T visit() {
        return value;
    }
};
// represents binary operations
template <typename T1, typename T2, typename T3>
class BinOp : public ASTNode<T3> {
public:
    ptr<ASTNode<T1>> left;
    ptr<ASTNode<T2>> right;
    char op{};
    BinOp(ptr<ASTNode<T1>> left, ptr<ASTNode<T2>> right, char op) {
        this->left = std::move(left);
        this->right = std::move(right);
        this->op = op;
        if constexpr((ISTYPE(T1, int)) && (ISTYPE(T2, int))) {
            this->type = Int;
        }
        // replace this later
//        else if (left.index() == String && right.index() == String) {
//            this->type = String;
//        }
//        else if (left.index() == Double && right.index() == Double) {
//            this->type = Double;
//        }
//        else if (left.index() == Int && right.index() == Double || right.index() == Int && left.index() == Double) {
//            this->type = Double;
//        }
        else {
            throw std::string("The LHS and RHS expressions are not compatible.");
        }
    }
    T3 visit() override;
};
template<>
inline int BinOp<int, int, int>::visit() {
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
class Print : public ASTNode<void> {
public:
    std::vector<node> exprs;
    void visit() override {
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
};
template <typename T>
class Var : public ASTNode<T> {
public:
    std::shared_ptr<Stack> st;
    std::string name;
    Var(std::string name, std::shared_ptr<Stack> st) : name(name) {this->st = st;}
    T visit() override;
};
template <>
inline int Var<int>::visit() {
    return std::get<int>(st->peek()[name]);
}
template <typename T>
class Assign : public ASTNode<void> {
public:
    ptr<Var<T>> var;
    ptr<ASTNode<T>> rhs; // trust trust
    Assign(ptr<Var<T>> var, ptr<ASTNode<T>> rhs) {
        this->var = std::move(var);
        this->rhs = std::move(rhs);
    }
    void visit() override {
        var->st->peek()[var->name] = rhs->visit();
    }
};
class Main : public ASTNode<void> {
public:
    std::vector<ptr<ASTNode<void>>> statements;
    void visit() override {
        for (auto & statement : statements) {
            statement->visit();
        }
    }
};
class Program : public ASTNode<void> {
public:
    ptr<Main> main;
    // TODO: add vector of functions
    void visit() override {
        main->visit();
    }
};
