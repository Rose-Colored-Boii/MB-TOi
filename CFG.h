
// Created by liam on 3/10/22.
//

#ifndef CFG_CFG_H
#define CFG_CFG_H
#include "vector"
#include "iostream"
#include "map"
using namespace std;


class CFG {
private:
    vector<string> variables;
    vector<string> terminals;
    map<string, vector<string>> productions;
    string startingVariable;
public:
    CFG();
    void print() const;

};


#endif //CFG_CFG_H