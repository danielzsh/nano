//
// Created by danie on 4/30/2022.
//

#include "Stack.h"
ActivationRecord::ActivationRecord() : members() {

}
Stack::Stack() {
    ActivationRecord ar;
    ar.name = "main";
    records.push_back(ar);
}
void Stack::push(ActivationRecord& ar) {
    records.push_back(ar);
}
void Stack::pop() {
    // cout << "The stack size is: " << records.size() << endl;
    records.pop_back();
}
ActivationRecord& Stack::peek() {
    // if (records.size() == 0) cout << "THERE ARE NO MORE RECORDS\n";
    return records.back();
}