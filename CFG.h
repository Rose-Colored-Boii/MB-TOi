
// Created by liam on 3/10/22.
//

#ifndef CFG_CFG_H
#define CFG_CFG_H
#include "vector"
#include "set"
#include "iostream"
#include "map"
#include "json.hpp"
#include "fstream"
#include "algorithm"
using namespace std;
using json = nlohmann::json;


class CFG {
private:
    vector<string> variables;
    vector<string> terminals;
    map<string, vector<string>> productions;
    string startingVariable;
    void elimNull();
public:
    CFG(const string& filename);
    void print() const;
    void toCNF();
    bool accepts(const string& input);
};


#endif //CFG_CFG_H
