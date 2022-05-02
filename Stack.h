//
// Created by danie on 4/30/2022.
//

#ifndef NANO_STACK_H
#define NANO_STACK_H
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <iostream>
using value = std::variant<int, double, std::string>;
class ActivationRecord {
public:
    std::map<std::string, value> members;
    std::string name;
    ActivationRecord();
    value& operator [] (std::string index) {
        return members[index];
    }
};
class Stack {
public:
    Stack();
    std::vector<ActivationRecord> records;
    void push(ActivationRecord& ar);
    void pop();
    ActivationRecord& peek();
};

#endif //NANO_STACK_H
