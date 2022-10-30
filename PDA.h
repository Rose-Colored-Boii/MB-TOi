//
// Created by liam on 27/10/2022.
//

#ifndef MB_TOI_PDA_H
#define MB_TOI_PDA_H
#include <vector>
#include <iostream>
#include <map>
#include <json.hpp>
#include <fstream>
#include "CFG.h"
using nlohmann::json;
using namespace std;

class PDA {
public:
    PDA(const string& filename);
    CFG toCFG();
private:
    vector<string> states;
    vector<string> alphabet;
    vector<string> stackAlphabet;
    map<vector<string>, vector<string>> transitions;
    string startState;
    vector<string> stack;
};


#endif //MB_TOI_PDA_H
